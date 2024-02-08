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
            char* currentReceivePtr = m_processBuffer.data() + m_bufferOffset;
            memcpy_s(currentReceivePtr, m_processBuffer.size() - m_bufferOffset, m_buffer.data().data(), bytesTransferred);

            char* nextRecvPtr = currentReceivePtr + bytesTransferred;

            ClientCommon::Header* header = reinterpret_cast<ClientCommon::Header*>(currentReceivePtr);
            short packetType = header->type;
            size_t packetSize = header->size;

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

    void Peer::ReceiveLeftData(char* currentReceivePtr, char* nextRecvPtr)
    {
        long long lnLeftData = nextRecvPtr - currentReceivePtr;

        if ((MAX_BUFFER - (nextRecvPtr - m_processBuffer.data())) < MIN_BUFFER)
        {
            // 패킷 처리 후 남은 데이터를 버퍼 시작 지점으로 복사
            memcpy(m_processBuffer.data(), currentReceivePtr, lnLeftData);
            currentReceivePtr = m_processBuffer.data();
            nextRecvPtr = currentReceivePtr + lnLeftData;
        }

        // 데이터를 받을 버퍼 세팅
        currentReceivePtr = nextRecvPtr;

        ReceiveData();
    }

    void Peer::Disconnect()
    {
        m_application->RemovePeer(m_id);
        cout << "[Debug: " << m_socket.remote_endpoint() << "] - client is disconnected\n";
    }

    void Peer::SendData(char* data, size_t size)
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