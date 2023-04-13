#include "stdafx.h"
#include "DBConnector.h"
#include "Logger.h"

DBConnector* DBConnector::s_instance = nullptr;

DBConnector::DBConnector()
{
}

DBConnector::~DBConnector()
{
	delete m_connection;
}

void DBConnector::Initialize()
{
	const std::string server = "127.0.0.1:3306";
	const std::string username = "root";
	const std::string password = "ljh915727!";

	try
	{
		m_driver = get_driver_instance();
		m_connection = m_driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		Log("Could not connect to server. Error message: %s", e.what());
		system("pause");
		exit(1);
	}

	m_connection->setSchema("smo");
}

sql::Connection* DBConnector::GetConnection() const
{
	return m_connection;
}

