#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class Sector;

class User : public ClientPeer
{
	short m_level{ 0 }, m_hp{ 0 }, m_x{ 0 }, m_y{ 0 };
	int m_nExp{ 0 };
	char m_sName[MAX_ID_LEN];

	std::mutex m_lock;
	int m_nLastMoveTime{ 0 };

	Sector* m_sector;

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

	Sector*& GetSector() { return m_sector; }
	Sector* const GetSector() const { return m_sector; }
#pragma endregion

	// 로그인

	void SetInfo(char* name, short level, int exp, short hp, short x, short y);
	void CompleteLogin();

	// 이동

	void ChangeSector(Sector* sector);
	void Move(short x, short y);
};