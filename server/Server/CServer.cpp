#include "stdafx.h"
#include "CServer.h"
#include "CommandHandlerFactory.h"
#include "User.h"
#include "Logger.h"
#include "Peer.h"

CServer CServer::s_instance;

CServer::CServer()
	: Core::BaseApplication()
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
	CommandHandlerFactory::GetInstance().Initialize();
}

shared_ptr<User> CServer::GetUser(const boost::uuids::uuid& id)
{
	lock_guard<mutex> lock{ m_userLock };
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
	shared_ptr<User> inst = make_shared<User>(peer);
	m_users.insert(make_pair(inst->id(), inst));
}

void CServer::OnDisconnected(Core::Peer* peer)
{
	lock_guard<mutex> lock{ m_userLock };

	auto result = m_users.find(peer->id());
	if (result != m_users.end())
	{
		auto toRemoveUser = result->second;
		m_users.erase(result);
		LogFormat("user count = %d", m_users.size());
	}
}
