#pragma once
#include"ClientPeer.h"

class Place;
class DBConnector;

class User : public ClientPeer, public std::enable_shared_from_this<User>
{
	short m_snLevel{ 0 }, m_snHp{ 0 }, m_snX{ 0 }, m_snY{ 0 };
	int m_nExp{ 0 };
	char m_sName[MAX_ID_LEN];

	std::mutex m_lock;
	int m_nLastMoveTime{ 0 };

	Place* m_place;

public:
	User(Peer* peer);
	virtual ~User();

#pragma region Properties
	const char* GetName() { return m_sName; }
	short GetLevel() const { return m_snLevel; }
	short GetHp() const { return m_snHp; }
	short GetX() const { return m_snX; }
	short GetY() const { return m_snY; }
	int GetExp() const { return m_nExp; }

	Place* GetPlace() const { return m_place; }
	Place*& GetPlace() { return m_place; }
#pragma endregion

	// 로그인

	void SetInfo(DBConnector* dbc);
	void SetInfo(char* name, short level, int exp, short hp, short x, short y, int placeId);

	// 이동

	void SetPosition(short x, short y);
};