#include "stdafx.h"
#include "User.h"
#include "RequestHandlerFactory.h"
#include "MetaDatas.h"
#include "DBWorker.h"

User::User(Peer* peer) : ClientPeer(peer, &RequestHandlerFactory::GetInstance())
{
}

User::~User()
{
}

void User::SetInfo(sql::ResultSet* result)
{
	int placeId = result->getInt("placeId");
	
	strcpy_s(m_sName, result->getString("name").c_str());
	m_snLevel = result->getInt("level");
	m_nExp = result->getInt("exp");
	m_snHp = result->getInt("hp");
	m_snX = result->getInt("x");
	m_snY = result->getInt("y");
	m_place = MetaDatas::GetInstance().GetPlace(placeId);
	m_place->AddUser(this);

	m_status = LoginStatus::LoggedIn;
}

void User::Logout()
{
	if (m_place)
		m_place->RemoveUser(GetID());

	if (m_status == LoginStatus::LoggedIn)
		DBWorker::UpdateUser(shared_from_this());

	m_status = LoginStatus::NotLogin;
}

void User::SetPosition(short x, short y)
{
	m_snX = x;
	m_snY = y;
}
