#include"stdafx.h"
#include "User.h"
#include"MetaDatas.h"

User::User(Peer* peer) : ClientPeer(peer, RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
	if (m_place)
		m_place->RemoveUser(this);
}

void User::SetInfo(char* name, short level, int exp, short hp, short x, short y)
{
	strcpy_s(this->m_sName, name);
	this->m_level = level;
	this->m_nExp = exp;
	this->m_hp = hp;
	this->m_x = x;
	this->m_y = y;
}

void User::CompleteLogin()
{
	Place* place = MetaDatas::GetInstance()->GetPlace(0);
	place->AddUser(this);
}

void User::Move(short x, short y)
{
	m_x = x;
	m_y = y;
}
