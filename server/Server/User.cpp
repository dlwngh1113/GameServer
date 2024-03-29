#include "stdafx.h"
#include "User.h"
#include "CommandHandlerFactory.h"
#include "Uuid.h"

User::User(Core::Peer* peer)
	: ClientPeer(peer, &CommandHandlerFactory::instance())
	, m_id(Core::Uuid::New())
{
}

User::~User()
{
}
