#include "stdafx.h"
#include "Peer.h"
#include "Uuid.h"
#include "BaseApplication.h"
#include "BaseCommandHandlerFactory.h"
#include "BaseCommandHandler.h"

namespace Core
{
    Peer::Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept
        : m_socket(move(socket))
        , m_buffer(m_data, MAX_BUFFER)
        , m_id(Uuid::New())
        , m_application(application)
        , m_factory(nullptr)
    {
        m_processBuffer.resize(MAX_BUFFER, '\0');
    }
    
    const boost::uuids::uuid& Peer::id() const
    {
        return m_id;
    }

    void Peer::ReceiveData()
    {
        try
        {
            boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer),
                bind(&Peer::OnReceiveData, shared_from_this(), placeholders::_1, placeholders::_2));
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }
    }
    
    void Peer::OnReceiveData(const boost::system::error_code& error, size_t bytesTransferred)
    {
        if (!error.failed())
        {
            // Process received data
            unsigned char* currentReceivePtr = m_processBuffer.data();
            memcpy_s(currentReceivePtr + m_bufferOffset, m_processBuffer.size() - m_bufferOffset, m_buffer.data(), m_buffer.size());

            unsigned char* nextRecvPtr = currentReceivePtr + bytesTransferred;

            ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(currentReceivePtr);
            short packetType = header->type;
            short packetSize = header->size;

            // 패킷이 size만큼 도착한 경우
            while (packetSize <= nextRecvPtr - currentReceivePtr)
            {
                ProcessPacket(currentReceivePtr, packetSize);

                currentReceivePtr += packetSize;
                if (currentReceivePtr < nextRecvPtr)
                {
                    header = reinterpret_cast<ClientCommon::Header*>(currentReceivePtr);
                    packetSize = header->size;
                }
                else
                    break;
            }

            ReceiveLeftData(currentReceivePtr, nextRecvPtr);
        }
        else
        {
            // Disconnect peer
            Disconnect();
        }
    }

    void Peer::ProcessPacket(unsigned char* data, size_t size)
    {
        ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(data);
        try
        {
            if (m_factory == nullptr)
                throw exception{ "CommandHandlerFactory is nullptr!" };

            shared_ptr<BaseCommandHandler> handler = m_factory->Create(header->type);
            handler->Initialize(shared_from_this(), header);

            // add to worker thread
            boost::asio::dispatch(BaseApplication::threads(), [handler]() { handler->Handle(); });
        }
        catch (exception& ex)
        {
            cout << "[Error] - " << ex.what() << endl;
        }
    }

    void Peer::ReceiveLeftData(unsigned char* currentReceivePtr, volatile unsigned char* nextRecvPtr)
    {
        long long lnLeftData = nextRecvPtr - currentReceivePtr;
        memcpy_s(m_processBuffer.data(), m_processBuffer.size(), currentReceivePtr, lnLeftData);

        // 데이터를 받을 버퍼 세팅
        m_bufferOffset = lnLeftData;

        ReceiveData();
    }

    void Peer::Disconnect()
    {
        m_application->RemovePeer(m_id);
        cout << "[Debug: " << m_socket.remote_endpoint() << "] - client is disconnected\n";
    }

    void Peer::SendData(char* data, size_t size)
    {
        try
        {
            boost::asio::async_write(m_socket, boost::asio::buffer(data, size),
                [](const boost::system::error_code& error, size_t bytesTransferred) {});
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }
    }

    shared_ptr<Peer> Peer::Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application )
    {
        shared_ptr<Peer> inst = make_shared<Peer>(move(socket), application);
        inst->ReceiveData();

        return inst;
    }
}