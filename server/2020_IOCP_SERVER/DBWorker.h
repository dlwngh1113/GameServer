#pragma once

class User;
class DBConnector;

class DBWorker
{
public:
	// MetaData
	static DBConnector* LoadMetaDatas();

	// User
	static void AddUser(char name[MAX_ID_LEN]);
	static std::shared_ptr<DBConnector> GetUser(char name[MAX_ID_LEN]);
	static void GetUser(std::shared_ptr<User> user, char name[MAX_ID_LEN]);
	static void UpdateUser(std::shared_ptr<User> user);
};