#pragma once

class DBConnector
{
private:
	const size_t m_connectionCount = 50;
	const std::string server = "127.0.0.1:3306";
	const std::string username = "root";
	const std::string password = "ljh915727!";

	static DBConnector s_instance;
	sql::Driver* m_driver;
	Concurrency::concurrent_queue<sql::Connection*> m_connections;

	DBConnector();
public:
	virtual ~DBConnector();
	DBConnector(const DBConnector& other) = delete;
	DBConnector& operator=(const DBConnector& other) = delete;

	void Initialize();
	std::unique_ptr<sql::Connection>GetConnection();
	void AddConnection(sql::Connection* conn);

	static DBConnector& GetInstance()
	{
		return s_instance;
	}
};