#include"stdafx.h"
#include "CServer.h"
#include "DBWorker.h"

CServer* CServer::m_instance = nullptr;

CServer::CServer() : BaseServer()
{
}

CServer::~CServer()
{
	Release();
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

void CServer::Release()
{
	for (auto& pair : m_users)
		if (pair.second)
			delete pair.second;

	m_users.clear();

	if (m_place)
		delete m_place;

	if (m_instance)
		delete m_instance;
}

void CServer::OnAccept(const SOCKET socket, Peer* peer)
{
	m_userLock.lock();
	m_users[socket] = new User(peer);
	m_userLock.unlock();
}

void CServer::OnDisconnected(const SOCKET socket)
{
	m_userLock.lock();
	User* toRemoveUser = m_users[socket];
	m_users.erase(socket);
	m_userLock.unlock();

	DBWorker::UpdateUser(toRemoveUser);

	if (toRemoveUser)
		delete toRemoveUser;
}
