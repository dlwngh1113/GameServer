#include "stdafx.h"
#include "Peer.h"
#include "Uuid.h"
#include "BaseApplication.h"

namespace Core
{
    Peer::Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept
        : m_socket(move(socket))
        , m_bufferOffset(0)
        , m_buffer(MAX_BUFFER)
        , m_id(Uuid::New())
        , m_application(application)
    {
    }
    
    const boost::uuids::uuid& Peer::id() const
    {
        return m_id;
    }

    boost::asio::ip::tcp::socket& Peer::socket()
    {
        return m_socket;
    }

    void Peer::ReceiveData()
    {
        boost::asio::async_read(m_socket, m_buffer,
            bind(&Peer::OnReceiveData, shared_from_this(), placeholders::_1, placeholders::_2));
    }
    
    void Peer::OnReceiveData(const boost::system::error_code& error, size_t bytesTransferred)
    {
        if (!error.failed())
        {
            // Process received data


            
            char* pNextRecvPos = m_receiveStartPtr + bytesTransferred;

            if (bytesTransferred < sizeof(ClientCommon::Header))
            {
                ReceiveLeftData(pNextRecvPos);
                return;
            }

            ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(m_receiveStartPtr);
            short snPacketType = header->type;
            short snPacketSize = header->size;

            // 패킷이 size만큼 도착한 경우
            while (snPacketSize <= pNextRecvPos - m_receiveStartPtr)
            {
                OnProcessPacket(m_receiveStartPtr, snPacketSize);

                m_receiveStartPtr += snPacketSize;
                if (m_receiveStartPtr < pNextRecvPos)
                {
                    header = reinterpret_cast<ClientCommon::Header*>(m_receiveStartPtr);
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

    void Peer::ReceiveLeftData(char* pNextRecvPos)
    {
        long long lnLeftData = pNextRecvPos - m_receiveStartPtr;

        if ((MAX_BUFFER - (pNextRecvPos - m_recvOver.iocpBuf)) < MIN_BUFFER)
        {
            // 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
            memcpy(m_recvOver.iocpBuf, m_receiveStartPtr, lnLeftData);
            m_receiveStartPtr = m_recvOver.iocpBuf;
            pNextRecvPos = m_receiveStartPtr + lnLeftData;
        }

        // 데이터를 받을 버퍼 세팅
        m_receiveStartPtr = pNextRecvPos;

        ReceiveData();
    }

    void Peer::Disconnect()
    {
        m_application->RemovePeer(m_id);
        cout << "[Debug: " << m_socket.remote_endpoint() << "] - client is disconnected\n";
    }

    void Peer::SendData(unsigned char* data, size_t size)
    {
        boost::asio::async_write(m_socket, boost::asio::buffer(data, size),
            [](const boost::system::error_code& error, size_t bytesTransferred) {});
    }

    shared_ptr<Peer> Peer::Create(boost::asio::ip::tcp::socket&& socket, BaseApplication* application)
    {
        shared_ptr<Peer> inst = make_shared<Peer>(move(socket), application);
        inst->ReceiveData();

        return inst;
    }
}