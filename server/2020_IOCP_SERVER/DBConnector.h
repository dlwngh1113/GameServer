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

	SQLWCHAR* m_query;

private:
	void Init();
	void Release();
	void CheckError();
	void ConvertToMultibyteQuery(const char* query);

public:
	DBConnector();
	virtual ~DBConnector();

	SQLHSTMT& GetStatement() { return m_hstmt; }

	void ExecuteDirectSQL();
	void PrepareStatement();
	void ExecutePreparedSQL();
	void SetQueryString(const char* statement);

	void AddParameter(int* val);
	void AddParameter(char* val);
};