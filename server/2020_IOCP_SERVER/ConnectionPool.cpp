#include "stdafx.h"
#include "ConnectionPool.h"
#include "Logger.h"

ConnectionPool ConnectionPool::s_instance;

ConnectionPool::ConnectionPool()
{
}

ConnectionPool::~ConnectionPool()
{
}

void ConnectionPool::Initialize()
{
	try
	{
		m_driver = get_driver_instance();
		for (int i = 0; i < m_connectionCount; ++i)
		{
			sql::Connection* conn = m_driver->connect(server, username, password);
			conn->setSchema("smo");
			m_connectionPool.push(conn);
		}
	}
	catch (sql::SQLException e)
	{
		Log(e.what());
		system("pause");
		exit(1);
	}
}

sql::Connection* ConnectionPool::GetConnection()
{
	std::unique_lock<std::mutex> lock{ m_lock };
	while (m_connectionPool.empty())
		m_conditionVariable.wait(lock);

	sql::Connection* conn = m_connectionPool.front();
	m_connectionPool.pop();

	return conn;
}

void ConnectionPool::ReleaseConnection(sql::Connection* conn)
{
	std::lock_guard<std::mutex> lock{ m_lock };
	m_connectionPool.push(conn);
	m_conditionVariable.notify_one();
}
