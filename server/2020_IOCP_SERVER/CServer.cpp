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

	if (m_instance)
		delete m_instance;
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

void CServer::OnAccept(const SOCKET socket, Peer*& peer)
{
	m_userLock.lock();
	m_users[socket] = new User(peer);
	m_userLock.unlock();
}

void CServer::OnDisconnected(SOCKET socket)
{
	m_userLock.lock();
	User* toRemoveUser = m_users[socket];
	m_users.erase(socket);
	m_userLock.unlock();

	delete toRemoveUser;
}
