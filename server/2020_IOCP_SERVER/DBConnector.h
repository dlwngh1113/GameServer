#pragma once

class DBConnector
{
private:
	const size_t m_connectionCount = 50;
	const std::string server = "127.0.0.1:3306";
	const std::string username = "root";
	const std::string password = "ljh915727!";

	static DBConnector* s_instance;
	sql::Driver* m_driver;
	Concurrency::concurrent_queue<sql::Connection*> m_connections;

	DBConnector();
public:
	virtual ~DBConnector();

	void Initialize();
	sql::Connection* GetConnection();

	static DBConnector* GetInstance()
	{
		if (!s_instance)
		{
			s_instance = new DBConnector();
		}

		return s_instance;
	}
};