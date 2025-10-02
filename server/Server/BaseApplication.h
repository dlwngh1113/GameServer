#pragma once
#include "Peer.h"

namespace Core
{
    class IWork;

    class BaseApplication
    {
    private:
        boost::asio::io_context m_context;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::lockfree::queue<IWork*> m_works;
        std::thread m_workerThread;

        std::unordered_map<boost::uuids::uuid, std::shared_ptr<Peer>, uuid_hash, uuid_equal> m_peers;

    public:
        BaseApplication();
        virtual ~BaseApplication();
        virtual void Run();

    private:
        void StartAccept();
        void TearDown();
        void OnAccept(const boost::system::error_code& error, boost::asio::ip::tcp::socket acceptedSocket);
        void Work();

        //
        // Peer
        //

    private:
        void AddPeer(std::shared_ptr<Peer> peer);
        void RemovePeer(std::shared_ptr<Peer> peer);
        std::shared_ptr<Peer> GetPeer(const boost::uuids::uuid& id);
    public:
        void DisconnectPeer(const boost::uuids::uuid& id);

        //
        //
        //

    protected:
        virtual void OnAccepted(Peer* peer) = 0;
        virtual void OnDisconnected(Peer* peer) = 0;
        virtual void OnTearDown() = 0;

    public:
        void EnqueueWork(std::function<void()> work);
    };
}