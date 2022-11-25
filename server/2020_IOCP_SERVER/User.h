#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class User : public ClientPeer
{
public:
	short level{ 0 }, hp{ 0 }, x{ 0 }, y{ 0 };
	int exp{ 0 };
	char name[MAX_ID_LEN];

	int lastMoveTime{ 0 };
	User(Peer* peer);
	virtual ~User();

	void SetInfo(char* name, short level, int exp, short hp, short x, short y);
};