#include"stdafx.h"
#include "CServer.h"
#include "DBWorker.h"
#include"MetaDatas.h"

CServer* CServer::m_instance = nullptr;

CServer::CServer() : BaseServer()
{
	Init();
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
	MetaDatas::GetInstance()->Init();
}

std::shared_ptr<User> CServer::GetUser(SOCKET key)
{
	return m_users[key];
}

void CServer::Release()
{
	m_users.clear();

	if (m_instance)
		delete m_instance;
}

void CServer::OnAccept(const SOCKET socket, std::shared_ptr<Peer> peer)
{
	m_userLock.lock();
	m_users[socket] = std::make_shared<User>(peer.get());
	m_userLock.unlock();
}

void CServer::OnDisconnected(const SOCKET socket)
{
	auto& toRemoveUser = m_users[socket];
	DBWorker::UpdateUser(toRemoveUser);
	
	m_userLock.lock();
	m_users.erase(socket);
	m_userLock.unlock();
}
