#include "stdafx.h"
#include "Peer.h"
#include "Uuid.h"
#include "BaseApplication.h"

namespace Core
{
    Peer::Peer(boost::asio::ip::tcp::socket&& socket, BaseApplication* application) noexcept
        : m_application(application)
        , m_socket(move(socket))
        , m_id(Uuid::New())
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
        if (error.failed())
        {
            // Disconnect peer
            Disconnect();
        }
        else
        {
            // Process received data
            ReceiveData();
        }
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
        return make_shared<Peer>(move(socket), application);
    }
}