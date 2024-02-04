#pragma once
#include "ClientPeer.h"

class Place;
class ConnectionPool;

enum class LoginStatus
{
	NotLogin,
	LoggingIn,
	LoggedIn
};

class User : public JCore::ClientPeer, public std::enable_shared_from_this<User>
{
	LoginStatus m_status;

	short m_snLevel{ 0 }, m_snHp{ 0 }, m_snX{ 0 }, m_snY{ 0 };
	int m_nExp{ 0 };
	char m_sName[MAX_ID_LEN];

	std::mutex m_lock;
	int m_nLastMoveTime{ 0 };

	Place* m_place{ nullptr };

public:
	explicit User(Peer* peer);
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
	LoginStatus GetStatus() const { return m_status; }
#pragma endregion

	// 로그인

	void SetInfo(sql::ResultSet* result);

	// 로그아웃

	void Logout();

	// 이동

	void SetPosition(short x, short y);
};