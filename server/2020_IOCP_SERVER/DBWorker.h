#pragma once

class User;

class DBWorker
{
public:
	// MetaData
	static sql::ResultSet* LoadMetaDatas();
	static sql::ResultSet* LoadPlaces();

	// User
	static void AddUser(char name[MAX_ID_LEN]);
	static void UpdateUser(std::shared_ptr<User> user);
	static sql::ResultSet* GetUser(char name[MAX_ID_LEN]);
};