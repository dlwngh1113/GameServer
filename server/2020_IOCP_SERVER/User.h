#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class User 
{
	ClientPeer* m_peer;
public:
	short x{ 0 }, y{ 0 };
	int lastMoveTime{ 0 };
	User(ClientPeer* peer);
	virtual ~User();
};