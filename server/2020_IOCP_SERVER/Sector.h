#pragma once
#include"User.h"

class Sector
{
private:
	std::unordered_set<User*> m_users;

public:

	void AddUser(User* user);
	void RemoveUser(User* user);
};

