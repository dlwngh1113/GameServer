#include "stdafx.h"
#include "User.h"
#include "RequestHandlerFactory.h"
#include "MetaDatas.h"

User::User(Core::Peer* peer) : ClientPeer(peer, &RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
}
