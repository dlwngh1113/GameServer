#pragma once
#include"User.h"

class Sector
{
private:
	int m_nX{ 0 }, m_nY{ 0 }, m_nWidth{ 0 }, m_nHeight{ 0 };
	std::unordered_set<User*> m_users;
	std::mutex m_lock;

public:
	Sector();
	virtual ~Sector();

	void AddUser(User* user);
	Sector* RemoveUser(User* user);

	void Init(int nX, int nY, int nWidth, int nHeight);
	bool IsPointInSector(short x, short y);
};