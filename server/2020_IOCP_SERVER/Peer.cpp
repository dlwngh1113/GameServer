#include "stdafx.h"
#include "Peer.h"
#include "Uuid.h"

namespace Core
{
    Peer::Peer(boost::asio::io_context& context)
        : m_socket(context)
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

    void Peer::ReceivePacket()
    {
        m_socket.async_receive(m_buffer, bind(&Peer::OnReceivedData, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    
    void Peer::OnReceivedData(const boost::system::error_code& error, size_t size)
    {
        if (error.failed())
            cout << "[Error] " << error.message() << endl;

        ReceivePacket();
    }

    void Peer::SendPacket(unsigned char* data, size_t size)
    {
        m_socket.async_send(boost::asio::buffer(data, size), []() {});
    }

    shared_ptr<Peer> Peer::Create(boost::asio::io_context& context)
    {
        return make_shared<Peer>(context);
    }
}