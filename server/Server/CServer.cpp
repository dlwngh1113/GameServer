#include "stdafx.h"
#include "CServer.h"
#include "CommandHandlerFactory.h"
#include "User.h"
#include "Logger.h"
#include "Peer.h"

namespace
{
	constexpr int WORLD_SIZE{ 800 };
}

CServer CServer::s_instance;

CServer::CServer()
	: Core::BaseApplication()
{
	Initialize();
}

void CServer::Run()
{
	Core::BaseApplication::Run();
}

void CServer::Initialize()
{
	CommandHandlerFactory::instance().Initialize();
	m_place = std::make_unique<Place>(0, WORLD_SIZE, WORLD_SIZE, SECTOR_SIZE, SECTOR_SIZE);
}

std::shared_ptr<User> CServer::GetUser(const boost::uuids::uuid& id)
{
	std::lock_guard<std::mutex> lock{ m_userLock };
	auto result = m_users.find(id);
	if (result != m_users.end())
		return result->second;

	return nullptr;
}

void CServer::OnTearDown()
{
	m_users.clear();
}

void CServer::OnAccepted(Core::Peer* peer)
{
	std::lock_guard<std::mutex> lock{ m_userLock };
	std::shared_ptr<User> inst = make_shared<User>(peer);
	m_users.insert(std::make_pair(inst->id(), inst));
}

void CServer::OnDisconnected(Core::Peer* peer)
{
	std::lock_guard<std::mutex> lock{ m_userLock };

	auto result = m_users.find(peer->id());
	if (result != m_users.end())
	{
		auto toRemoveUser = result->second;
		m_users.erase(result);
	}
}
