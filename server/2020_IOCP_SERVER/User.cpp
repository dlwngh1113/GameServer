#include"stdafx.h"
#include "User.h"

User::User(ClientPeer* peer)
{
	m_peer = peer;
	m_peer->Init(RequestHandlerFactory::GetInstance());
}

User::~User()
{
}