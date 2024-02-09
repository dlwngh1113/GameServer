#pragma once
#include "Peer.h"

namespace Core
{
    class BaseApplication
    {
    private:
        boost::asio::io_context m_context;
        boost::asio::ip::tcp::acceptor m_acceptor;

        unordered_map<boost::uuids::uuid, shared_ptr<Peer>, uuid_hash, uuid_equal> m_peers;

    public:
        BaseApplication();
        ~BaseApplication();
        virtual void Run();

    private:
        void StartAccept();
        void OnAccept(const boost::system::error_code& error, boost::asio::ip::tcp::socket acceptedSocket);

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

        // Static member variables
    private:
        static boost::asio::thread_pool s_threads;

        // Static member functions
    public:
        static boost::asio::thread_pool& threads() { return s_threads; };
    };
}