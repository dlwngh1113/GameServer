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
        , m_currentReceivePos(m_data)
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
  
        unsigned char* currentBufferPos = reinterpret_cast<unsigned char*>(m_buffer.data());
        unsigned char* pNextRecvPos = currentBufferPos + bytesTransferred;

        if (bytesTransferred < sizeof(Common::Header))
        {
            ReceiveLeftData(pNextRecvPos);
            return;
        }

        Common::Header* header = reinterpret_cast<Common::Header*>(currentBufferPos);
        auto packetSize = header->size;

        // 패킷이 size만큼 도착한 경우
        while (packetSize <= pNextRecvPos - currentBufferPos)
        {
            ProcessPacket(currentBufferPos, packetSize);

            currentBufferPos += packetSize;
            if (currentBufferPos < pNextRecvPos)
            {
                header = reinterpret_cast<Common::Header*>(currentBufferPos);
                packetSize = header->size;
            }
            else
                break;
        }

        ReceiveLeftData(pNextRecvPos);
    }

    void Peer::ProcessPacket(unsigned char* data, size_t size)
    {
        Common::Header* header = reinterpret_cast<Common::Header*>(data);
        try
        {
            if (m_factory == nullptr)
                throw std::exception{ "CommandHandlerFactory is nullptr!" };

            std::shared_ptr<BaseCommandHandler> handler = m_factory->Create(header->type);
            handler->Initialize(shared_from_this(), data, size);

            // add to worker thread
            boost::asio::dispatch(m_application->threads(), [handler]() { handler->Handle(); });
        }
        catch (std::exception& ex)
        {
            Logger::instance().Log(std::format("[Error] - {}", ex.what()));
        }
    }

    void Peer::ReceiveLeftData(unsigned char* nextRecvPtr)
    {
        unsigned char* currentReceivePos = reinterpret_cast<unsigned char*>(m_buffer.data());
        long long lnLeftData = nextRecvPtr - currentReceivePos;

        if ((MAX_BUFFER - (nextRecvPtr - currentReceivePos)) < MIN_BUFFER)
        {
            // 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
            memcpy(m_data, currentReceivePos, lnLeftData);
            m_buffer = boost::asio::mutable_buffer(m_data, MAX_BUFFER);
            nextRecvPtr = m_data + lnLeftData;
        }

        m_buffer = boost::asio::mutable_buffer(nextRecvPtr, MAX_BUFFER - lnLeftData);

        ReceiveData();
    }

    void Peer::Disconnect()
    {
        m_application->DisconnectPeer(m_id);
        //Logger::instance().Log(format("[Debug: {}] - client is disconnected", m_socket.remote_endpoint().address().to_string()));
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