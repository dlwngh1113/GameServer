#include "stdafx.h"
#include "DBConnector.h"
#include "Logger.h"

DBConnector::DBConnector()
{
	Init();
}

DBConnector::DBConnector(const char* query) : DBConnector()
{
	SetQueryString(query);
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
				Log("DB Allocate success");
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
	Log((char*)m_sMessage);
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
		Log("Query Prepare Success");
	else
		CheckError();
}

void DBConnector::ExecutePreparedStatement()
{
	SQLRETURN retCode = SQLExecute(m_hstmt);

	if (retCode == SQL_SUCCESS)
		Log("Prepared Query Execute Success");
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
		Log("Allocate Handle Success");
	else
		CheckError();
}

void DBConnector::AddParameter(int val)
{
	SQLBindParameter(m_hstmt, ++m_nParamIndex, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &val, 0, NULL);
}

void DBConnector::AddParameter(short val)
{
	SQLBindParameter(m_hstmt, ++m_nParamIndex, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &val, 0, NULL);
}

void DBConnector::AddParameter(const char* val)
{
	SQLBindParameter(m_hstmt, ++m_nParamIndex, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, strlen(val), 0, (SQLCHAR*)const_cast<char*>(val), 0, NULL);
}
