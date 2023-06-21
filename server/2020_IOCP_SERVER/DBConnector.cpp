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

std::unique_ptr<DBConnection> DBConnector::GetConnection()
{
	sql::Connection* con;
	if (m_connectionPool.size())
	{
		std::lock_guard lock{ m_lock };
		con = std::move(m_connectionPool.front());
		con->reconnect();
		m_connectionPool.pop();
	}
	else
		con = m_driver->connect(server, username, password);

	// 스키마 설정
	con->setSchema("smo");

	std::unique_ptr<DBConnection> conn = std::make_unique<DBConnection>();
	conn->SetConnection(con);

	return conn;
}

void DBConnector::ReturnConnection(sql::Connection*& conn)
{
	m_lock.lock();
	m_connectionPool.push(conn);
	m_lock.unlock();
}