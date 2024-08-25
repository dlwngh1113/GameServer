#pragma once
#include "User.h"

class Sector
{
private:
	int m_nX{ 0 }, m_nY{ 0 }, m_nWidth{ 0 }, m_nHeight{ 0 };
	std::unordered_set<std::shared_ptr<User>> m_users;
	std::mutex m_lock;

	void SendUserEnter(std::shared_ptr<User> user);
	void SendUserExit(std::shared_ptr<User> targetUser);

public:
	Sector();
	virtual ~Sector();
	void Init(int nX, int nY, int nWidth, int nHeight);

	int getX() const { return m_nX / m_nWidth; }
	int getY() const { return m_nY / m_nHeight; }

	void Move(std::shared_ptr<User> targetUser);
	void AddUser(std::shared_ptr<User> user);
	void RemoveUser(std::shared_ptr<User> user);

	bool IsPointInSector(short x, short y);
};
