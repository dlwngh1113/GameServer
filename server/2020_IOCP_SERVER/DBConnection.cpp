#include "stdafx.h"
#include "DBConnection.h"
#include "DBConnector.h"

DBConnection::DBConnection(sql::Connection* conn)
{
	m_connection = conn;
}

DBConnection::~DBConnection()
{
	DBConnector::GetInstance().ReturnConnection(m_connection);
}
