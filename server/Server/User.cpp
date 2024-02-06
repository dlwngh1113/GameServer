#include "stdafx.h"
#include "User.h"
#include "RequestHandlerFactory.h"
#include "MetaDatas.h"
#include "Uuid.h"

User::User(Core::Peer* peer)
	: ClientPeer(peer, &RequestHandlerFactory::GetInstance())
	, m_id(Core::Uuid::New())
{
}

User::~User()
{
}
