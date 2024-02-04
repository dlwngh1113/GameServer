#include "pch.h"
#include "Peer.h"

namespace JCore
{
    Peer::Peer(boost::asio::io_context& context)
        : m_socket(context)
    {
    }

    const boost::asio::ip::tcp::socket& Peer::socket() const
    {
        return m_socket;
    }

    boost::asio::ip::tcp::socket& Peer::socket()
    {
        return m_socket;
    }

    shared_ptr<Peer> JCore::Peer::Create(boost::asio::io_context& context)
    {
        return make_shared<Peer>(context);
    }
}