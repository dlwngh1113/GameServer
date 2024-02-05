#include "stdafx.h"
#include "Peer.h"
#include "Uuid.h"
#include "BaseApplication.h"

namespace Core
{
    Peer::Peer(boost::asio::io_context& context, BaseApplication* application)
        : m_application(application)
        , m_socket(context)
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
        m_socket.async_receive(m_buffer, bind(&Peer::OnReceiveData, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    
    void Peer::OnReceiveData(const boost::system::error_code& error, size_t size)
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
        m_application->RemovePeer(shared_from_this());
        cout << "[Debug: " << m_socket.remote_endpoint() << "] - client is disconnected\n";
    }

    void Peer::SendData(unsigned char* data, size_t size)
    {
        m_socket.async_send(boost::asio::buffer(data, size), []() {});
    }

    shared_ptr<Peer> Peer::Create(boost::asio::io_context& context, BaseApplication* application)
    {
        return make_shared<Peer>(context, application);
    }
}