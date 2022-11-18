#include "stdafx.h"
#include "DBConnector.h"

DBConnector::DBConnector()
{
	Init();
}

DBConnector::~DBConnector()
{
	Release();
}

void DBConnector::Init()
{
	dbRetcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	dbRetcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	dbRetcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
	dbRetcode = SQLConnect(hdbc, (SQLWCHAR*)L"g_server", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);
}

void DBConnector::Release()
{
	SQLCancel(hstmt);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
}
