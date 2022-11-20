#pragma once
#include"Logger.h"

class DBConnector
{
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt = 0;

	SQLSMALLINT m_nLenth;
	SQLINTEGER m_nRecord, m_nNative;
	SQLWCHAR m_sState[7], m_sMessage[256];
public:
	DBConnector();
	virtual ~DBConnector();

	void Init();
	void Release();

	void GetUserData();
};