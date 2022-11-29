#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class User : public ClientPeer
{
	short m_level{ 0 }, m_hp{ 0 }, m_x{ 0 }, m_y{ 0 };
	int m_nExp{ 0 };
	char m_sName[MAX_ID_LEN];

	int m_nLastMoveTime{ 0 };

public:
	User(Peer* peer);
	virtual ~User();

#pragma region Properties
	char* const GetName() { return m_sName; }
	short GetLevel() const { return m_level; }
	short GetHp() const { return m_hp; }
	short GetX() const { return m_x; }
	short GetY() const { return m_y; }
	short GetExp() const { return m_nExp; }
#pragma endregion

	void SetInfo(char* name, short level, int exp, short hp, short x, short y);
	void Teleport(short x, short y);
	void Move(short dx, short dy, int nMoveTime);
};