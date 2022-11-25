#pragma once
#include"Logger.h"

class DBConnector
{
	SQLHENV m_henv;
	SQLHDBC m_hdbc;
	SQLHSTMT m_hstmt = 0;
	int m_nParamIndex{ 0 };

	SQLSMALLINT m_nLenth;
	SQLINTEGER m_nRecord, m_nNative;
	SQLWCHAR m_sState[7], m_sMessage[UCHAR_MAX];

private:
	void Init();
	void Release();
	void CheckError();

public:
	DBConnector();
	virtual ~DBConnector();

	SQLHSTMT& GetStatement() { return m_hstmt; }

	void ExecuteDirectSQL(SQLWCHAR* statement);
	SQLWCHAR* ConvertToMultibyteQuery(const char* query);
	void PrepareStatement(SQLWCHAR* statement);
	void ExecutePreparedSQL();
	void AddParameter(int* val);
	void AddParameter(char* val);
};