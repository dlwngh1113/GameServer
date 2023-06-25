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

sql::Connection* ConnectionPool::CreateConnection()
{
	sql::Connection* conn = m_driver->connect(m_connectionProperties);
	return conn;
}

void ConnectionPool::Initialize()
{
	m_connectionProperties["hostName"] = "127.0.0.1";
	m_connectionProperties["userName"] = "root";
	m_connectionProperties["password"] = "ljh915727!";
	m_connectionProperties["schema"] = "smo";
	m_connectionProperties["port"] = 3306;

	try
	{
		m_driver = get_driver_instance();

		for (int i = 0; i < m_connectionCount; ++i)
			m_connectionPool.push(CreateConnection());
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

	//while (m_connectionPool.empty())
	//	m_conditionVariable.wait(lock);

	//sql::Connection* conn = m_connectionPool.front();
	//m_connectionPool.pop();

	sql::Connection* conn;
	if (!m_connectionPool.empty())
	{
		conn = m_connectionPool.front();
		m_connectionPool.pop();
	}
	else
		conn = m_driver->connect(m_connectionProperties);

	return conn;
}

void ConnectionPool::ReleaseConnection(sql::Connection* conn)
{
	std::lock_guard<std::mutex> lock{ m_lock };
	m_connectionPool.push(conn);
	m_conditionVariable.notify_one();
}
