#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class User : public ClientPeer
{
public:
	short x{ 0 }, y{ 0 };
	int lastMoveTime{ 0 };
	User(Peer* peer);
	virtual ~User();
};