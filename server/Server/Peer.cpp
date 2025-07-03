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
        , m_buffer(m_data, MAX_BUFFER)
        , m_id(Uuid::New())
        , m_application(application)
        , m_factory(nullptr)
        , m_currentBufferPos(m_data)
    {
    }

    Peer::~Peer() noexcept
    {
    }
    
    const boost::uuids::uuid& Peer::id() const
    {
        return m_id;
    }

    void Peer::ReceiveData()
    {
        try
        {
            m_socket.async_receive(boost::asio::buffer(m_buffer),
                bind(&Peer::OnReceiveData, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
        catch (std::exception& ex)
        {
            Logger::instance().Log(ex.what());
        }
    }
    
    void Peer::OnReceiveData(const boost::system::error_code& error, size_t bytesTransferred)
    {
        if (error.failed())
        {
            Disconnect();
            return;
        }
  
        uint8_t* pNextRecvPos = m_currentBufferPos + bytesTransferred;

        if (bytesTransferred < sizeof(Common::Header))
        {
            ReceiveLeftData(pNextRecvPos);
            return;
        }

        Common::Header header{};
        memcpy(&header, m_currentBufferPos, sizeof(header));

        while (header.size <= pNextRecvPos - m_currentBufferPos)
        {
            ProcessPacket(header.type, header.size);

            m_currentBufferPos += header.size;
            if (m_currentBufferPos < pNextRecvPos)
            {
                memcpy(&header, m_currentBufferPos, sizeof(header));
            }
            else
                break;
        }

        ReceiveLeftData(pNextRecvPos);
    }

    void Peer::ProcessPacket(int16_t type, int16_t size)
    {
        try
        {
            if (m_factory == nullptr)
                throw std::exception{ "CommandHandlerFactory is nullptr!" };

            std::shared_ptr<BaseCommandHandler> handler = m_factory->Create(type);
            handler->Initialize(shared_from_this(), m_currentBufferPos, size);

            m_application->EnqueueWork([handler]() { handler->Handle(); });
        }
        catch (std::exception& ex)
        {
            Logger::instance().Log(std::format("[Error] - {}", ex.what()));
        }
    }

    void Peer::ReceiveLeftData(uint8_t* nextRecvPtr)
    {
        long long lnLeftData = nextRecvPtr - m_currentBufferPos;

        if ((MAX_BUFFER - (nextRecvPtr - m_currentBufferPos)) < MIN_BUFFER)
        {
            // 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
            memcpy(m_data, m_currentBufferPos, lnLeftData);
            m_buffer = boost::asio::mutable_buffer(m_data, MAX_BUFFER);
            nextRecvPtr = m_data + lnLeftData;
        }

        m_buffer = boost::asio::mutable_buffer(nextRecvPtr, MAX_BUFFER - lnLeftData);
        m_currentBufferPos = nextRecvPtr;

        ReceiveData();
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
        catch (std::exception& ex)
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
        catch (std::exception& ex)
        {
            Logger::instance().Log(ex.what());
        }
    }

    std::shared_ptr<Peer> Peer::Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application )
    {
        std::shared_ptr<Peer> inst = std::make_shared<Peer>(std::move(socket), application);
        inst->ReceiveData();

        return inst;
    }
}