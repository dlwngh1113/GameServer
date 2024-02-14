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
            // [LJH_TODO]
            //  이거 왜 안됨?
            //boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer),
            m_socket.async_receive(boost::asio::buffer(m_buffer),
                bind(&Peer::OnReceiveData, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
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
            /*
            unsigned char* pNextRecvPos = m_pReceiveStartPtr + ioSize;

            if (ioSize < sizeof(Header))
            {
                ReceiveLeftData(pNextRecvPos);
                return;
            }

            Header* header = reinterpret_cast<Header*>(m_pReceiveStartPtr);
            short snPacketType = header->type;
            short snPacketSize = header->size;

            // 패킷이 size만큼 도착한 경우
            while (snPacketSize <= pNextRecvPos - m_pReceiveStartPtr)
            {
                OnProcessPacket(m_pReceiveStartPtr, snPacketSize);

                m_pReceiveStartPtr += snPacketSize;
                if (m_pReceiveStartPtr < pNextRecvPos)
                {
                    header = reinterpret_cast<Header*>(m_pReceiveStartPtr);
                    snPacketSize = header->size;
                }
                else
                    break;
            }

            ReceiveLeftData(pNextRecvPos);
            */

            unsigned char* pNextRecvPos = reinterpret_cast<unsigned char*>(m_buffer.data()) + bytesTransferred;

            if (bytesTransferred < sizeof(ClientCommon::Header))
            {
                ReceiveLeftData(pNextRecvPos);
                return;
            }

            ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(m_buffer.data());
            short snPacketType = header->type;
            short snPacketSize = header->size;

            // 패킷이 size만큼 도착한 경우
            while (snPacketSize <= pNextRecvPos - m_buffer.data())
            {
                ProcessPacket(reinterpret_cast<unsigned char*>(m_buffer.data()), snPacketSize);

                m_buffer += snPacketSize;
                if (m_buffer.data() < pNextRecvPos)
                {
                    header = reinterpret_cast<ClientCommon::Header*>(m_buffer.data());
                    snPacketSize = header->size;
                }
                else
                    break;
            }

            ReceiveLeftData(pNextRecvPos);
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

    void Peer::ReceiveLeftData(unsigned char* nextRecvPtr)
    {
        long long lnLeftData = nextRecvPtr - m_buffer.data();

        if ((MAX_BUFFER - (nextRecvPtr - m_buffer.data())) < MIN_BUFFER)
        {
            // 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
            memcpy(m_data, m_buffer.data(), lnLeftData);
            m_buffer = boost::asio::mutable_buffer(m_data, MAX_BUFFER);
            nextRecvPtr = m_data + lnLeftData;
        }

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