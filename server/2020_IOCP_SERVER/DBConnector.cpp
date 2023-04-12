#include "stdafx.h"
#include "DBConnector.h"
#include "Logger.h"

DBConnector::DBConnector()
{
	const std::string server = "tcp://yourservername.mysql.database.azure.com:3306";
	const std::string username = "username@servername";
	const std::string password = "yourpassword";

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

	m_connection->setSchema("g_server");
}

DBConnector::~DBConnector()
{
}

sql::Statement* DBConnector::GetStatement()
{
	return m_connection->createStatement();
}

sql::PreparedStatement* DBConnector::GetPreparedStatement(const char* sSql)
{
	return m_connection->prepareStatement(sSql);
}
