#include "stdafx.h"
#include "BaseApplication.h"

namespace Core
{
    boost::asio::thread_pool BaseApplication::s_threads(MAX_THREAD_COUNT);

    BaseApplication::BaseApplication()
        : m_acceptor(m_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SERVER_PORT))
    {
    }

    BaseApplication::~BaseApplication()
    {
        s_threads.join();
        m_context.stop();
        m_acceptor.close();
    }

    void BaseApplication::Run()
    {
        StartAccept();

        m_context.run();
    }

    void BaseApplication::StartAccept()
    {
        shared_ptr<boost::asio::ip::tcp::socket> socket = make_shared<boost::asio::ip::tcp::socket>(m_context);
        m_acceptor.async_accept(bind(&BaseApplication::OnAccept, this, placeholders::_1, socket));
    }

    void BaseApplication::OnAccept(const boost::system::error_code& error, shared_ptr<boost::asio::ip::tcp::socket> acceptedSocket)
    {
        // Successfully accpeted new peer
        if (!error)
        {
            cout << acceptedSocket->remote_endpoint() << " is connected!\n";

            shared_ptr<Peer> acceptedPeer = Peer::Create(move(*acceptedSocket), this);
            AddPeer(acceptedPeer);
            OnAccepted(acceptedPeer.get());
        }

        StartAccept();
    }

    //
    // Peer
    //

    void BaseApplication::RemovePeer(const boost::uuids::uuid& id)
    {
        m_peers.erase(id);
    }

    void BaseApplication::AddPeer(shared_ptr<Peer> peer)
    {
        m_peers.insert(make_pair(peer->id(), peer));
    }
}