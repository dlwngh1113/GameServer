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
		m_place->RemoveUser(GetID());
}

void User::SetInfo(sql::ResultSet* result)
{
	result->next();
	auto name = result->getString("name");
	int level = result->getInt("level");
	int x = result->getInt("x");
	int y = result->getInt("y");
	int exp = result->getInt("exp");
	int hp = result->getInt("hp");
	int placeId = result->getInt("placeId");
	
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
