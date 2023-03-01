#pragma once
#include"DBConnector.h"

class User;

class DBWorker
{
public:
	static void GetUser(std::shared_ptr<User> user, char name[MAX_ID_LEN]);
	static void UpdateUser(std::shared_ptr<User>& user);
};