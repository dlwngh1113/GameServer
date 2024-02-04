#pragma once
#include "Peer.h"

namespace JCore
{
    class BaseApplication
    {
    private:
        boost::asio::io_context& m_context;
        boost::asio::ip::tcp::acceptor m_acceptor;

    public:
        BaseApplication(boost::asio::io_context& io_context);

    private:
        void StartAccept();
        void HandleAccept(shared_ptr<Peer> acceptedPeer, const boost::system::error_code& error);
    };
}