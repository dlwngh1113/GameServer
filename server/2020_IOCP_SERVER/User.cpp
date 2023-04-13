#include "stdafx.h"
#include "User.h"
#include "DBConnector.h"
#include "RequestHandlerFactory.h"
#include "MetaDatas.h"

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
	short level = result->getInt(2);
	short x = result->getInt(3);
	short y = result->getInt(4);
	short exp = result->getInt(5);
	short hp = result->getInt(6);
	short placeId = result->getInt(7);

	strcpy_s(this->m_sName, result->getString(1)->c_str());
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
