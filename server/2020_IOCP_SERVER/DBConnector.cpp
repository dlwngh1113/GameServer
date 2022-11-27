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
	SQLRETURN dbRetcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
	if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO)
	{
		dbRetcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
		if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO)
		{
			dbRetcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
			if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO)
				Logger::Info("DB Allocate success");
			else
				CheckError();
		}
		else
			CheckError();
	}
	else
		CheckError();

	SQLConnect(m_hdbc, (SQLWCHAR*)L"g_server", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);
}

void DBConnector::Release()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	SQLDisconnect(m_hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
	delete[] m_query;
}

void DBConnector::CheckError()
{
	SQLGetDiagRec(SQL_HANDLE_DBC, m_hdbc, ++m_nRecord, m_sState, &m_nNative, m_sMessage, UCHAR_MAX, &m_nLenth);
	Logger::Error((char*)m_sMessage);
}

void DBConnector::ExecuteDirectSQL()
{
	SQLRETURN retCode = SQLExecDirect(m_hstmt, m_query, SQL_NTS);
	if (retCode != SQL_SUCCESS)
		CheckError();
}

void DBConnector::PrepareStatement()
{
	SQLRETURN retCode = SQLPrepare(m_hstmt, m_query, SQL_NTS);

	if (retCode == SQL_SUCCESS)
		Logger::Info("\nQuery Prepare Success\n");
	else
		CheckError();
}

void DBConnector::ExecutePreparedStatement()
{
	SQLRETURN retCode = SQLExecute(m_hstmt);

	if (retCode == SQL_SUCCESS)
		Logger::Info("\nPrepared Query Execute Success\n");
	else
		CheckError();
}

void DBConnector::SetQueryString(const char* query)
{
	int nChars = MultiByteToWideChar(CP_ACP, 0, query, -1, NULL, 0);
	wchar_t* tQuery = new wchar_t[nChars];
	MultiByteToWideChar(CP_ACP, 0, query, -1, (LPWSTR)tQuery, nChars);
	m_query = (SQLWCHAR*)tQuery;

	SQLRETURN retCode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if (retCode == SQL_SUCCESS || retCode == SQL_SUCCESS_WITH_INFO)
		Logger::Info("Allocate Handle Success");
	else
		CheckError();
}

void DBConnector::AddParameter(int* val)
{
	SQLBindParameter(m_hstmt, ++m_nParamIndex, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(val), 0, val, 0, NULL);
}

void DBConnector::AddParameter(char* val)
{
	SQLBindParameter(m_hstmt, ++m_nParamIndex, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(val), 0, val, 0, NULL);
}

//void DBConnector::GetUserData()
//{
//	SQLRETURN dbRetcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
//	char getQuery[MAX_STR_LEN] = { NULL };
//	sprintf_s(getQuery, "EXEC GetUser %s", p->name);
//
//	int nChars = MultiByteToWideChar(CP_ACP, 0, getQuery, -1, NULL, 0);
//	wchar_t* pwcsName = new wchar_t[nChars];
//	MultiByteToWideChar(CP_ACP, 0, getQuery, -1, (LPWSTR)pwcsName, nChars);
//
//	dbRetcode = SQLExecDirect(hstmt, (SQLWCHAR*)pwcsName, SQL_NTS);
//
//	if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO) 
//	{
//		SQLINTEGER LEVEL, EXP;
//		SQLSMALLINT POSX, POSY, HP;
//		SQLLEN cbLevel, cbExp, cbPosX, cbPosY, cbHp;
//		// Bind columns 1, 2, and 3  
//		dbRetcode = SQLBindCol(hstmt, 1, SQL_C_LONG, &LEVEL, 100, &cbLevel);
//		dbRetcode = SQLBindCol(hstmt, 2, SQL_C_SHORT, &POSX, 100, &cbPosX);
//		dbRetcode = SQLBindCol(hstmt, 3, SQL_C_SHORT, &POSY, 100, &cbPosY);
//		dbRetcode = SQLBindCol(hstmt, 4, SQL_C_LONG, &EXP, 100, &cbExp);
//		dbRetcode = SQLBindCol(hstmt, 5, SQL_C_SHORT, &HP, 100, &cbHp);
//
//		dbRetcode = SQLFetch(hstmt);
//		if (dbRetcode == SQL_ERROR || dbRetcode == SQL_SUCCESS_WITH_INFO)
//			std::cout << "code line 388 error\n";
//		if (dbRetcode == SQL_SUCCESS || dbRetcode == SQL_SUCCESS_WITH_INFO)
//		{
//			printf("%s %d %d %d %d %d", p->name, LEVEL, POSX, POSY, EXP, HP);
//			client->SetInfo(p->name, LEVEL, POSX, POSY, EXP, HP);
//		}
//	}
//
//	delete[] pwcsName;
//}