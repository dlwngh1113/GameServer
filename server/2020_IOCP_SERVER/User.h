#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class User 
{
	ClientPeer* m_peer;
public:
	User(ClientPeer* peer);
	virtual ~User();
};