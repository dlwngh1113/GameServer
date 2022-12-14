#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class Place;

class User : public ClientPeer
{
	short m_level{ 0 }, m_hp{ 0 }, m_x{ 0 }, m_y{ 0 };
	int m_nExp{ 0 };
	char m_sName[MAX_ID_LEN];

	std::mutex m_lock;
	int m_nLastMoveTime{ 0 };

	Place* m_place;

public:
	User(Peer* peer);
	virtual ~User();

#pragma region Properties
	char* const GetName() { return m_sName; }
	short GetLevel() const { return m_level; }
	short GetHp() const { return m_hp; }
	short GetX() const { return m_x; }
	short GetY() const { return m_y; }
	int GetExp() const { return m_nExp; }

	Place* GetPlace() const { return m_place; }
	Place*& GetPlace() { return m_place; }
#pragma endregion

	// 로그인

	void SetInfo(char* name, short level, int exp, short hp, short x, short y);

	// 이동

	void SetPosition(short x, short y);
};