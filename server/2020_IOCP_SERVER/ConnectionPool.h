#pragma once

class ConnectionPool
{
private:
	const size_t m_connectionCount = 50;
	sql::ConnectOptionsMap m_connectionProperties;

	static ConnectionPool s_instance;
	std::queue<sql::Connection*> m_connectionPool;
	std::mutex m_lock;
	std::condition_variable m_conditionVariable;
	sql::Driver* m_driver;

private:
	ConnectionPool();
	sql::Connection* CreateConnection();

public:
	virtual ~ConnectionPool();
	ConnectionPool(const ConnectionPool& other) = delete;
	ConnectionPool& operator=(const ConnectionPool& other) = delete;
	void Initialize();

	sql::Connection* GetConnection();
	void ReleaseConnection(sql::Connection* conn);

	static ConnectionPool& GetInstance()
	{
		return s_instance;
	}
};