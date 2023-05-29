#include "stdafx.h"
#include "DBConnector.h"
#include "Logger.h"

DBConnector DBConnector::s_instance;

DBConnector::DBConnector()
{
}

DBConnector::~DBConnector()
{
	sql::Connection* conn;
	while (m_connections.try_pop(conn))
	{
		delete conn;
	}
}

void DBConnector::Initialize()
{
	try
	{
		m_driver = get_driver_instance();
		sql::Connection* conn;
		for (auto i = 0; i < m_connectionCount; ++i)
		{
			conn= m_driver->connect(server, username, password);
			conn->setSchema("smo");
			m_connections.push(conn);
		}
	}
	catch (sql::SQLException e)
	{
		Log("Could not connect to server. Error message: %s", e.what());
		system("pause");
		exit(1);
	}
}

sql::Connection* DBConnector::GetConnection()
{
	sql::Connection* conn;
	if (m_connections.try_pop(conn))
		return conn;

	conn = m_driver->connect(server, username, password);
	conn->setSchema("smo");

	return conn;
}

void DBConnector::AddConnection(sql::Connection* conn)
{
	conn->close();
	m_connections.push(conn);
}

