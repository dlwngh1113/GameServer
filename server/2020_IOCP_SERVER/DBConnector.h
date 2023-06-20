#pragma once

#include "DBConnection.h"

class DBConnector
{
private:
	const size_t m_connectionCount = 50;
	const std::string server = "127.0.0.1:3306";
	const std::string username = "root";
	const std::string password = "ljh915727!";

	static DBConnector s_instance;
	std::queue<sql::Connection*> m_connectionPool;
	sql::Driver* m_driver;

	DBConnector();
public:
	virtual ~DBConnector();
	DBConnector(const DBConnector& other) = delete;
	DBConnector& operator=(const DBConnector& other) = delete;

	void Initialize();
	std::unique_ptr<DBConnection> GetConnection();
	void ReturnConnection(sql::Connection* conn);

	static DBConnector& GetInstance()
	{
		return s_instance;
	}
};