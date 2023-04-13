#include "stdafx.h"
#include "User.h"
#include "DBConnector.h"
#include "RequestHandlerFactory.h"
#include "MetaDatas.h"

#include "Logger.h"

User::User(Peer* peer) : ClientPeer(peer, RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
	if (m_place)
		m_place->RemoveUser(std::make_shared<User>(m_peer));
}

void User::SetInfo(sql::ResultSet* result)
{
	auto name = result->getString(1);
	int level = result->getInt(2);
	int x = result->getInt(3);
	int y = result->getInt(4);
	int exp = result->getInt(5);
	int hp = result->getInt(6);
	int placeId = result->getInt(7);
	
	Log("place Id = %s %d", name.c_str(), level);

	strcpy_s(this->m_sName, name.c_str());
	this->m_snLevel = level;
	this->m_nExp = exp;
	this->m_snHp = hp;
	this->m_snX = x;
	this->m_snY = y;
	this->m_place = MetaDatas::GetInstance()->GetPlace(placeId);
}

void User::SetPosition(short x, short y)
{
	m_snX = x;
	m_snY = y;
}
