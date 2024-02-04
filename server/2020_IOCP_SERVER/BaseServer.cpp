#include "pch.h"
#include "BaseApplication.h"

namespace JCore
{
    BaseApplication::BaseApplication(boost::asio::io_context& io_context)
        : m_context(io_context)
        , m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SERVER_PORT))
    {
        StartAccept();
    }

    void BaseApplication::StartAccept()
    {
        shared_ptr<Peer> acceptedPeer = Peer::Create(m_context);

        m_acceptor.async_accept(acceptedPeer->socket(),
            bind(&BaseApplication::HandleAccept, this, acceptedPeer,
                boost::asio::placeholders::error));
    }

    void BaseApplication::HandleAccept(shared_ptr<Peer> acceptedPeer, const boost::system::error_code& error)
    {
        // Successfully accpeted new peer
        if (!error)
        {
        }

        StartAccept();
    }
}