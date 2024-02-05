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

        m_acceptor.async_accept(&BaseApplication::HandleAccept);
    }

    void BaseApplication::HandleAccept(const boost::system::error_code& error, shared_ptr<Peer> acceptedPeer)
    {
        // Successfully accpeted new peer
        if (!error)
        {
            AddPeer(acceptedPeer);
            OnAccepted(acceptedPeer.get());
            acceptedPeer->ReceiveData();
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