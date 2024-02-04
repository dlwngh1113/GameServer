#include "pch.h"
#include "Peer.h"
#include "Uuid.h"

namespace JCore
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