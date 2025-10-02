#include "stdafx.h"
#include "BaseApplication.h"
#include "DataBase.h"
#include "Logger.h"
#include "PacketWork.h"

namespace Core
{
    BaseApplication::BaseApplication()
        : m_acceptor{ m_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SERVER_PORT) }
        , m_works{ 100 }
        , m_workerThread{ &BaseApplication::Work, this }
    {
    }

    BaseApplication::~BaseApplication()
    {
        TearDown();
    }

    void BaseApplication::Run()
    {
        DataBase::instance().Initialize();
        
        Logger::instance().Log("Server is running...");

        StartAccept();

        m_context.run();
    }

    void BaseApplication::StartAccept()
    {
        m_acceptor.async_accept(bind(&BaseApplication::OnAccept, this, std::placeholders::_1, std::placeholders::_2));
    }

    void BaseApplication::TearDown()
    {
        Logger::instance().Log("OnTearDown starting...");
        OnTearDown();
        Logger::instance().Log("OnTearDown finished...");

        m_workerThread.join();
        m_context.stop();
        m_acceptor.close();
    }

    void BaseApplication::OnAccept(const boost::system::error_code& error, boost::asio::ip::tcp::socket acceptedSocket)
    {
        // Successfully accpeted new peer
        if (!error)
        {
            std::shared_ptr<Peer> acceptedPeer = Peer::Create(std::move(acceptedSocket), this);
            AddPeer(acceptedPeer);
            OnAccepted(acceptedPeer.get());
        }
        else
        {
            Logger::instance().Log(error.message());
        }

        StartAccept();
    }

    void BaseApplication::Work()
    {
        while (true)
        {
            IWork* work{ nullptr };
            if (m_works.pop(work))
            {
                work->Execute();
                delete work;
            }
        }
    }

    //
    // Peer
    //

    void BaseApplication::DisconnectPeer(const boost::uuids::uuid& id)
    {
        std::shared_ptr<Peer> peer = GetPeer(id);
        if (peer)
        {
            RemovePeer(peer);
            OnDisconnected(peer.get());
        }
    }

    std::shared_ptr<Peer> BaseApplication::GetPeer(const boost::uuids::uuid& id)
    {
        auto it = m_peers.find(id);
        if (it != m_peers.end())
            return it->second;

        return nullptr;
    }

    void BaseApplication::RemovePeer(std::shared_ptr<Peer> peer)
    {
        m_peers.erase(peer->id());
    }

    void BaseApplication::AddPeer(std::shared_ptr<Peer> peer)
    {
        m_peers.insert(std::make_pair(peer->id(), peer));
    }

    void BaseApplication::EnqueueWork(std::function<void()> work)
    {
        m_works.push(new PacketWork{work});
    }
}