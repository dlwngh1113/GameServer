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
        m_processBuffer.resize(MAX_BUFFER);
    }
    
    const boost::uuids::uuid& Peer::id() const
    {
        return m_id;
    }

    void Peer::ReceiveData()
    {
        try
        {
            boost::asio::async_read(m_socket, m_buffer,
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
            // If buffer is full, move buffer to bigger size
            if (m_bufferOffset + bytesTransferred >= m_processBuffer.size())
                m_processBuffer.resize(m_bufferOffset + bytesTransferred);

            // Process received data
            char* currentReceivePtr = m_processBuffer.data();
            memcpy_s(currentReceivePtr + m_bufferOffset, m_processBuffer.size() - m_bufferOffset, m_buffer.data().data(), bytesTransferred);

            char* nextRecvPtr = currentReceivePtr + bytesTransferred;

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

    void Peer::ReceiveLeftData(char* currentReceivePtr, char* nextRecvPtr)
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