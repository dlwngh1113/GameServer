#pragma once
#include"DBConnector.h"

class User;

class DBWorker
{
public:
	static void GetUser(User* user, char name[MAX_ID_LEN]);
	static void UpdateUser(User* user);
};