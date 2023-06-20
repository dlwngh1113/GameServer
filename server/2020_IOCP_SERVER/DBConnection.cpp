#include "stdafx.h"
#include "DBConnection.h"

DBConnection::DBConnection(sql::Connection*& conn)
{
	m_connection = conn;
}

DBConnection::~DBConnection()
{
}

sql::Connection* DBConnection::operator->()
{
	return m_connection;
}
