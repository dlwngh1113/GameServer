#include"stdafx.h"
#include "CServer.h"

CServer* CServer::m_instance = nullptr;

CServer::CServer() : BaseServer()
{
}

CServer::~CServer()
{
	for (auto& pair : m_users)
		delete pair.second;

	m_users.clear();
}

void CServer::Run()
{
	BaseServer::Run();
}

void CServer::Init()
{
	RequestHandlerFactory::GetInstance()->Init();
}

User* CServer::GetUser(SOCKET key)
{
	return m_users[key];
}

void CServer::OnAccept(const SOCKET socket, ClientPeer*& peer)
{
	m_userLock.lock();
	m_users[socket] = new User(peer);
	m_userLock.unlock();
}
