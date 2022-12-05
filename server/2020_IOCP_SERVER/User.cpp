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
	strcpy_s(this->m_sName, name);
	this->m_level = level;
	this->m_nExp = exp;
	this->m_hp = hp;
	this->m_x = x;
	this->m_y = y;
}

void User::Teleport(short x, short y)
{
	this->m_x = x;
	this->m_y = y;
}

void User::ChangeSector(Sector* sector)
{
	m_lock.lock();
	m_sector = sector;
	m_lock.unlock();
}

void User::Move(short dx, short dy, int nMoveTime)
{
	if (m_nLastMoveTime + 1 >= nMoveTime)
		return;

	Teleport(m_x + dx, m_y + dy);
	m_nLastMoveTime = nMoveTime;
}
