#include "stdafx.h"
#include "User.h"
#include "DBConnector.h"
#include "RequestHandlerFactory.h"
#include "MetaDatas.h"
#include "Logger.h"

User::User(Peer* peer) : ClientPeer(peer, &RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
	if (m_place)
		m_place->RemoveUser(GetID());
}

void User::SetInfo(sql::ResultSet* result)
{
	int placeId = result->getInt("placeId");
	
	strcpy_s(this->m_sName, result->getString("name").c_str());
	this->m_snLevel = result->getInt("level");
	this->m_nExp = result->getInt("exp");
	this->m_snHp = result->getInt("hp");
	this->m_snX = result->getInt("x");
	this->m_snY = result->getInt("y");
	this->m_place = MetaDatas::GetInstance().GetPlace(placeId);

	m_status = LoginStatus::LoggedIn;
}

void User::SetPosition(short x, short y)
{
	m_snX = x;
	m_snY = y;
}
