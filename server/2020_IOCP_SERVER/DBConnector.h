#pragma once

class DBConnector
{
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt = 0;
	SQLRETURN dbRetcode;
public:
	DBConnector();
	virtual ~DBConnector();

	void Init();
	void Release();
};