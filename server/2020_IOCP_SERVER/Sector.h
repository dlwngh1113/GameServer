#pragma once
#include"User.h"

class Sector
{
private:
	int m_nX{ 0 }, m_nY{ 0 }, m_nWidth{ 0 }, m_nHeight{ 0 };
	std::unordered_set<User*> m_users;

public:
	Sector(int nX, int nY, int nWidth, int nHeight);
	virtual ~Sector();

	void AddUser(User* user);
	void RemoveUser(User* user);
};	