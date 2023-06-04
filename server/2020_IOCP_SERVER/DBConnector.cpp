#include "stdafx.h"
#include "DBConnector.h"
#include "Logger.h"

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
	}
	catch (sql::SQLException e)
	{
		Log(e.what());
		system("pause");
		exit(1);
	}
}

std::unique_ptr<sql::Connection>DBConnector::GetConnection()
{
	std::unique_ptr<sql::Connection> conn{ m_driver->connect(server,username,password) };
	conn->setSchema("smo");

	return conn;
}
