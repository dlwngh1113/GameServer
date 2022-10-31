#include"stdafx.h"
#include "CServer.h"

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
	BaseServer::Init();
	RequestHandlerFactory::GetInstance()->Init();
}

void CServer::OnAccept(const SOCKET socket)
{
	m_userLock.lock();
	m_users[socket] = new User(RequestHandlerFactory::GetInstance());
	m_userLock.unlock();
}
