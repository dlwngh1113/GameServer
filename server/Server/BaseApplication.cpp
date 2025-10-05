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
            Peer* acceptedPeer = Peer::Create(std::move(acceptedSocket), this);
            AddPeer(acceptedPeer);
            OnAccepted(acceptedPeer);
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
        Peer* peer = GetPeer(id);
        if (!peer)
            return;
     
        OnDisconnected(peer);
        RemovePeer(peer);
    }

    Peer* BaseApplication::GetPeer(const boost::uuids::uuid& id)
    {
        auto it = m_peers.find(id);
        return it != m_peers.end() ? it->second : nullptr;
    }

    void BaseApplication::RemovePeer(Peer* peer)
    {
        m_peers.erase(peer->id());
        SAFE_DELETE(peer);
    }

    void BaseApplication::AddPeer(Peer* peer)
    {
        m_peers.emplace(peer->id(), peer);
    }

    void BaseApplication::EnqueueWork(std::function<void()> work)
    {
        m_works.push(new PacketWork{work});
    }
}