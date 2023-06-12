#include "stdafx.h"
#include "CServer.h"
#include "DBWorker.h"
#include "DBConnector.h"
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
	DBConnector::GetInstance().Initialize();
	MetaDatas::GetInstance().Initialize();
}

std::shared_ptr<User> CServer::GetUser(SOCKET key)
{
	return m_users[key];
}

void CServer::Release()
{
	m_users.clear();
}

void CServer::OnAccept(const SOCKET socket, Peer* peer)
{
	m_userLock.lock();
	m_users[socket] = std::make_shared<User>(peer);
	m_userLock.unlock();
}

void CServer::OnDisconnected(const SOCKET socket)
{
	auto toRemoveUser = m_users[socket];

	toRemoveUser->Logout();
	
	m_userLock.lock();
	m_users.erase(socket);
	m_userLock.unlock();
}
