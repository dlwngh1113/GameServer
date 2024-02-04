#pragma once
#include "Peer.h"

namespace JCore
{
	class BOOST_SYMBOL_EXPORT BaseApplication
	{
    public:
        BaseApplication(boost::asio::io_context& io_context)
            : m_context(io_context),
            m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13))
        {
            start_accept();
        }

    private:
        void start_accept()
        {
            shared_ptr<Peer> acceptedPeer = Peer::Create(m_context);

            m_acceptor.async_accept(acceptedPeer->socket(),
                bind(&tcp_server::handle_accept, this, acceptedPeer,
                    boost::asio::placeholders::error));
        }

        void handle_accept(tcp_connection::pointer acceptedPeer,
            const boost::system::error_code& error)
        {
            if (!error)
            {
                acceptedPeer->start();
            }

            start_accept();
        }

        boost::asio::io_context& m_context;
        boost::asio::ip::tcp::acceptor m_acceptor;
}