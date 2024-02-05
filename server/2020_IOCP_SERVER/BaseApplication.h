#pragma once
#include "Peer.h"

namespace Core
{
    class BaseApplication
    {
    private:
        boost::asio::io_context& m_context;
        boost::asio::ip::tcp::acceptor m_acceptor;

        unordered_map<boost::uuids::uuid, shared_ptr<Peer>> m_peers;

    public:
        BaseApplication(boost::asio::io_context& io_context);
        virtual void Run();

    private:
        void StartAccept();
        void HandleAccept(shared_ptr<Peer> acceptedPeer, const boost::system::error_code& error);

        //
        // Peer
        //

    private:
        void AddPeer(shared_ptr<Peer> peer);
    public:
        void RemovePeer(const boost::uuids::uuid& id);

        //
        //
        //

    protected:
        virtual void OnAccepted(Peer* peer) = 0;
        virtual void OnDisconnected(Peer* peer) = 0;
    };
}