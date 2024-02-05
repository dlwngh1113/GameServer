#include "stdafx.h"
#include "BaseApplication.h"

namespace Core
{
    BaseApplication::BaseApplication(boost::asio::io_context& io_context)
        : m_context(io_context)
        , m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SERVER_PORT))
    {
    }

    void BaseApplication::Run()
    {
        StartAccept();
    }

    void BaseApplication::StartAccept()
    {
        shared_ptr<Peer> acceptedPeer = Peer::Create(m_context, this);

        m_acceptor.async_accept(acceptedPeer->socket(),
            bind(&BaseApplication::HandleAccept, this, acceptedPeer,
                boost::asio::placeholders::error));
    }

    void BaseApplication::HandleAccept(shared_ptr<Peer> acceptedPeer, const boost::system::error_code& error)
    {
        // Successfully accpeted new peer
        if (!error)
        {
            AddPeer(acceptedPeer);
            acceptedPeer->ReceiveData();
        }

        StartAccept();
    }

    //
    // Peer
    //

    void BaseApplication::RemovePeer(shared_ptr<Peer> peer)
    {
        m_peers.erase(peer->id());
    }

    void BaseApplication::AddPeer(shared_ptr<Peer> peer)
    {
        m_peers.insert(make_pair(peer->id(), peer));
    }
}