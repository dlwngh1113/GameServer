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

void User::SetInfo(DBConnector* dbc)
{
	short level, hp, x, y;
	int exp, placeId;
	SQLLEN cLevel, cHp, cX, cY, cExp, cYPlaceId;

	SQLBindCol(dbc->GetStatement(), 2, SQL_C_SHORT, &level, sizeof(level), &cLevel);
	SQLBindCol(dbc->GetStatement(), 3, SQL_C_LONG, &exp, sizeof(exp), &cExp);
	SQLBindCol(dbc->GetStatement(), 4, SQL_C_SHORT, &hp, sizeof(hp), &cHp);
	SQLBindCol(dbc->GetStatement(), 5, SQL_C_SHORT, &x, sizeof(x), &cX);
	SQLBindCol(dbc->GetStatement(), 6, SQL_C_SHORT, &y, sizeof(y), &cY);
	SQLBindCol(dbc->GetStatement(), 7, SQL_C_LONG, &placeId, sizeof(placeId), &cYPlaceId);

	SetInfo(m_sName, level, exp, hp, x, y, placeId);
}

void User::SetInfo(char* name, short level, int exp, short hp, short x, short y, int placeId)
{
	strcpy_s(this->m_sName, name);
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
