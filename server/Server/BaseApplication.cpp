#include "stdafx.h"
#include "BaseApplication.h"
#include "DataBase.h"
#include "Logger.h"

namespace Core
{
    BaseApplication::BaseApplication()
        : m_acceptor(m_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SERVER_PORT))
        , m_threads(MAX_THREAD_COUNT)
    {
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

        m_threads.join();
        m_context.stop();
        m_acceptor.close();
    }

    void BaseApplication::OnAccept(const boost::system::error_code& error, boost::asio::ip::tcp::socket acceptedSocket)
    {
        // Successfully accpeted new peer
        if (!error)
        {
            Logger::instance().Log(format("{} is connected!", acceptedSocket.remote_endpoint().address().to_string()));

            std::shared_ptr<Peer> acceptedPeer = Peer::Create(std::move(acceptedSocket), this);
            AddPeer(acceptedPeer);
            OnAccepted(acceptedPeer.get());
        }

        StartAccept();
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
        std::lock_guard<std::mutex> lock{ m_lock };
        auto it = m_peers.find(id);
        if (it != m_peers.end())
            return it->second;

        return nullptr;
    }

    void BaseApplication::RemovePeer(std::shared_ptr<Peer> peer)
    {
        std::lock_guard<std::mutex> lock{ m_lock };
        m_peers.erase(peer->id());
    }

    void BaseApplication::AddPeer(std::shared_ptr<Peer> peer)
    {
        std::lock_guard<std::mutex> lock{ m_lock };
        m_peers.insert(std::make_pair(peer->id(), peer));
    }
}