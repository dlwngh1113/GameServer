#include"stdafx.h"
#include "User.h"
#include"RequestHandlerFactory.h"
#include"MetaDatas.h"

User::User(Peer* peer) : ClientPeer(peer, RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
	if (m_place)
		m_place->RemoveUser(std::make_shared<User>(m_peer));
}

void User::SetInfo(char* name, short level, int exp, short hp, short x, short y)
{
	strcpy_s(this->m_sName, name);
	this->m_snLevel = level;
	this->m_nExp = exp;
	this->m_snHp = hp;
	this->m_snX = x;
	this->m_snY = y;
}

void User::SetPosition(short x, short y)
{
	m_snX = x;
	m_snY = y;
}
