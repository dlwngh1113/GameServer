#include "stdafx.h"
#include "CServer.h"
#include "DBWorker.h"
#include "ConnectionPool.h"
#include "Place.h"
#include "MetaDatas.h"
#include "RequestHandlerFactory.h"
#include "User.h"
#include "Logger.h"
#include "Peer.h"

CServer CServer::s_instance;

CServer::CServer(boost::asio::io_context context)
	: Core::BaseApplication(context)
{
	Initialize();
}

CServer::~CServer()
{
	Release();
}

void CServer::Run()
{
	Core::BaseApplication::Run();
}

void CServer::Initialize()
{
	RequestHandlerFactory::GetInstance().Initialize();
	ConnectionPool::GetInstance().Initialize();
	MetaDatas::GetInstance().Initialize();
}

std::shared_ptr<User> CServer::GetUser(const boost::uuids::uuid& id)
{
	std::lock_guard<std::mutex> lock{ m_userLock };
	auto result = m_users.find(id);
	if (result != m_users.end())
		return result->second;

	return nullptr;
}

void CServer::Release()
{
	m_users.clear();
}

void CServer::OnAccepted(Core::Peer* peer)
{
	lock_guard<mutex> lock{ m_userLock };
	m_users.insert(make_pair(peer->id(), make_shared<User>(peer)));
}

void CServer::OnDisconnected(Core::Peer* peer)
{
	std::lock_guard<std::mutex> lock{ m_userLock };

	auto result = m_users.find(peer->id());
	if (result != m_users.end())
	{
		auto toRemoveUser = result->second;
		toRemoveUser->Logout();
		m_users.erase(socket);
		LogFormat("user count = %d", m_users.size());
	}
}
