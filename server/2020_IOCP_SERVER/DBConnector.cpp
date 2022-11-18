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

void DBConnector::GetUserData()
{
	dbRetcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	char getQuery[MAX_STR_LEN] = { NULL };
	sprintf_s(getQuery, "EXEC get_userdata %s", p->name);

	int nChars = MultiByteToWideChar(CP_ACP, 0, getQuery, -1, NULL, 0);
	wchar_t* pwcsName = new wchar_t[nChars];
	MultiByteToWideChar(CP_ACP, 0, getQuery, -1, (LPWSTR)pwcsName, nChars);

	dbRetcode = SQLExecDirect(hstmt, (SQLWCHAR*)pwcsName, SQL_NTS);

	if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO) 
	{
		SQLINTEGER LEVEL, EXP;
		SQLSMALLINT POSX, POSY, HP;
		SQLLEN cbLevel, cbExp, cbPosX, cbPosY, cbHp;
		// Bind columns 1, 2, and 3  
		dbRetcode = SQLBindCol(hstmt, 1, SQL_C_LONG, &LEVEL, 100, &cbLevel);
		dbRetcode = SQLBindCol(hstmt, 2, SQL_C_SHORT, &POSX, 100, &cbPosX);
		dbRetcode = SQLBindCol(hstmt, 3, SQL_C_SHORT, &POSY, 100, &cbPosY);
		dbRetcode = SQLBindCol(hstmt, 4, SQL_C_LONG, &EXP, 100, &cbExp);
		dbRetcode = SQLBindCol(hstmt, 5, SQL_C_SHORT, &HP, 100, &cbHp);

		dbRetcode = SQLFetch(hstmt);
		if (dbRetcode == SQL_ERROR || dbRetcode == SQL_SUCCESS_WITH_INFO)
			std::cout << "code line 388 error\n";
		if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO)
		{
			printf("%s %d %d %d %d %d", p->name, LEVEL, POSX, POSY, EXP, HP);
			client->SetInfo(p->name, LEVEL, POSX, POSY, EXP, HP);
		}
	}

	delete[] pwcsName;
}