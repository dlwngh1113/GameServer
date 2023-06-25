#pragma once

class User;

class DBWorker
{
public:
	// MetaData
	static std::unique_ptr<sql::ResultSet> LoadMetaDatas();
	static std::unique_ptr<sql::ResultSet> LoadPlaces();

	// User
	static std::unique_ptr<sql::PreparedStatement> GetOrCreateUser(char name[MAX_ID_LEN]);
	static void AddUser(char name[MAX_ID_LEN]);
	static void UpdateUser(std::shared_ptr<User> user);
	static std::unique_ptr<sql::ResultSet> GetUser(char name[MAX_ID_LEN]);
};