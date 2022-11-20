#pragma once
#include"Logger.h"

class DBConnector
{
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt = 0;
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
	void ExecuteDirectSQL(SQLWCHAR* sStatement);
	SQLWCHAR* ConvertToMultibyteQuery(const char* query);
	void AddParameter(int* val);
	void AddParameter(char* val);
};