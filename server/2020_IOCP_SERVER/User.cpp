#include"stdafx.h"
#include "User.h"

User::User(Peer* peer) : ClientPeer(peer, RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
}

void User::SetInfo(char* name, short level, int exp, short hp, short x, short y)
{
	strcpy_s(this->name, name);
	this->level = level;
	this->exp = exp;
	this->hp = hp;
	this->x = x;
	this->y = y;
}
