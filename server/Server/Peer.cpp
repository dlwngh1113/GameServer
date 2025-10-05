#include "stdafx.h"
#include "Peer.h"
#include "BaseApplication.h"
#include "BaseCommandHandlerFactory.h"
#include "BaseCommandHandler.h"
#include "Logger.h"

namespace Core
{
    Peer::Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept
        : m_socket(std::move(socket))
        , m_buffer(MAX_BUFFER)
        , m_id(Uuid::New())
        , m_application(application)
        , m_factory(nullptr)
    {
    }

    Peer::~Peer() noexcept
    {
        m_socket.close();
        m_application = nullptr;
        m_factory = nullptr;
    }
    
    const boost::uuids::uuid& Peer::id() const
    {
        return m_id;
    }

    void Peer::ReceiveData()
    {
        try
        {
            m_socket.async_receive(boost::asio::buffer(m_buffer.GetWriteBuffer(), m_buffer.GetWriteBufferSize()),
                bind(&Peer::OnReceiveData, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
        catch (std::runtime_error& ex)
        {
            Logger::instance().Log(ex.what());
        }
    }
    
    void Peer::OnReceiveData(const boost::system::error_code& error, int32_t bytesTransferred)
    {
        if (error.failed())
        {
            Disconnect();
            return;
        }

        auto leftBytes = bytesTransferred;
        m_buffer.AddReceivedSize(leftBytes);

        if (leftBytes < static_cast<int32_t>(sizeof(Common::Header)))
        {
            ReceiveData();
            return;
        }
  
        static thread_local uint8_t pBuffer[MAX_BUFFER]{};
        m_buffer.Peek(pBuffer, leftBytes);

        Common::Header header{};
        do
        {
            m_buffer.Peek(reinterpret_cast<uint8_t*>(&header), sizeof(header));

            ProcessPacket(header.type, header.size);

            leftBytes -= header.size;
            m_buffer.Pop(pBuffer, header.size);
        } while (m_buffer.GetReadableSize() > 0);

        ReceiveData();
    }

    void Peer::ProcessPacket(int16_t type, int16_t size)
    {
        try
        {
            if (m_factory == nullptr)
                throw std::runtime_error{ "CommandHandlerFactory is nullptr!" };

            std::shared_ptr<BaseCommandHandler> handler = m_factory->Create(type);
            handler->Initialize(this, m_buffer.GetReadBuffer(), size);

            m_application->EnqueueWork([handler]() { handler->Handle(); });
        }
        catch (std::runtime_error& ex)
        {
            Logger::instance().Log(std::format("[Error] - {}", ex.what()));
        }
    }

    void Peer::Disconnect()
    {
        m_application->DisconnectPeer(m_id);
    }

    void Peer::SendData(std::shared_ptr<Common::Packet> packet)
    {
        Common::PacketStream ps;
        std::string data = packet->Serialize(ps);

        SendData(data);
    }

    void Peer::SendData(const std::string& data)
    {
        try
        {
            m_socket.async_send(boost::asio::buffer(data),
                [](const boost::system::error_code& error, size_t bytesTransferred) {});
        }
        catch (std::runtime_error& ex)
        {
            Logger::instance().Log(ex.what());
        }
    }

    void Peer::SendData(char* data, size_t size)
    {
        try
        {
            m_socket.async_send(boost::asio::buffer(data, size),
                [](const boost::system::error_code& error, size_t bytesTransferred) {});
        }
        catch (std::runtime_error& ex)
        {
            Logger::instance().Log(ex.what());
        }
    }

    Peer* Peer::Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application )
    {
        Peer* inst = new Peer(std::move(socket), application);
        inst->ReceiveData();

        return inst;
    }
}