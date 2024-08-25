#include "stdafx.h"
#include "User.h"
#include "CommandHandlerFactory.h"
#include "Uuid.h"

User::User(Core::Peer* peer)
	: ClientPeer(peer, &CommandHandlerFactory::instance())
	, m_id(peer->id())
{
}

User::~User()
{
}

void User::Login(std::shared_ptr<sql::ResultSet> user)
{
	m_userId = user->getString("id");
	m_x = static_cast<float>(user->getDouble("x"));
	m_y = static_cast<float>(user->getDouble("y"));
}

void User::Teleport(float x, float y)
{
	m_x = x;
	m_y = y;
}

void User::Move(float x, float y)
{
	m_x = x;
	m_y = y;
}
