#include "stdafx.h"
#include "CServer.h"
#include "DBWorker.h"
#include "ConnectionPool.h"
#include "Place.h"
#include "MetaDatas.h"
#include "RequestHandlerFactory.h"
#include "User.h"

CServer CServer::s_instance;

CServer::CServer() : BaseServer()
{
	Initialize();
}

CServer::~CServer()
{
	Release();
}

void CServer::Run()
{
	BaseServer::Run();
}

void CServer::Initialize()
{
	RequestHandlerFactory::GetInstance().Initialize();
	ConnectionPool::GetInstance().Initialize();
	MetaDatas::GetInstance().Initialize();
}

std::shared_ptr<User> CServer::GetUser(SOCKET key)
{
	std::lock_guard<std::mutex> lock{ m_userLock };
	auto result = m_users.find(key);
	if (result != m_users.end())
		return result->second;

	return nullptr;
}

void CServer::Release()
{
	m_users.clear();
}

void CServer::OnAccept(const SOCKET socket, Peer* peer)
{
	std::lock_guard<std::mutex> lock{ m_userLock };
	m_users.insert(std::pair<SOCKET, std::shared_ptr<User>>(socket, std::make_shared<User>(peer)));
}

void CServer::OnDisconnected(const SOCKET socket)
{
	std::lock_guard<std::mutex> lock{ m_userLock };

	auto result = m_users.find(socket);
	if (result != m_users.end())
	{
		auto toRemoveUser = result->second;
		toRemoveUser->Logout();
		m_users.erase(socket);
	}
}
