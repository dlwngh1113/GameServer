#include "stdafx.h"
#include "DBConnector.h"
#include "Logger.h"
#include "DBConnection.h"

DBConnector DBConnector::s_instance;

DBConnector::DBConnector()
{
}

DBConnector::~DBConnector()
{
}

void DBConnector::Initialize()
{
	try
	{
		m_driver = get_driver_instance();
		for (int i = 0; i < m_connectionCount; ++i)
		{
			sql::Connection* conn = m_driver->connect(server, username, password);
			m_connectionPool.emplace(conn);
		}
	}
	catch (sql::SQLException e)
	{
		Log(e.what());
		system("pause");
		exit(1);
	}
}

std::unique_ptr<DBConnection>DBConnector::GetConnection()
{
	sql::Connection* conn = m_connectionPool.front();
	std::unique_ptr<DBConnection> conn{ m_connectionPool.front() };
	conn->operator->()->setSchema("smo");

	return conn;
}
