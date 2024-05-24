#include "stdafx.h"
#include "BaseApplication.h"
#include "DataBase.h"
#include "Logger.h"

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
        DataBase::instance().Initialize();

        Logger::instance().Log("Server is running...");

        StartAccept();

        m_context.run();
    }

    void BaseApplication::StartAccept()
    {
        m_acceptor.async_accept(bind(&BaseApplication::OnAccept, this, std::placeholders::_1, std::placeholders::_2));
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

    void BaseApplication::RemovePeer(const boost::uuids::uuid& id)
    {
        m_peers.erase(id);
    }

    void BaseApplication::AddPeer(std::shared_ptr<Peer> peer)
    {
        m_peers.insert(std::make_pair(peer->id(), peer));
    }
}