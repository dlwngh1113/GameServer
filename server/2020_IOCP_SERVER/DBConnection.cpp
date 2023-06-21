#include "stdafx.h"
#include "DBConnection.h"
#include "DBConnector.h"

DBConnection::DBConnection()
{
}

DBConnection::~DBConnection()
{
	m_connection->close();
	DBConnector::GetInstance().ReturnConnection(m_connection);
}
