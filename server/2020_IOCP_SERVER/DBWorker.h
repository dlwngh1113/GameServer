#pragma once

class User;

class DBWorker
{
public:
	static void AddUser(char name[ClientCommon::MAX_ID_LEN]);
	static void GetUser(std::shared_ptr<User> user, char name[ClientCommon::MAX_ID_LEN]);
	static void UpdateUser(std::shared_ptr<User> user);
};