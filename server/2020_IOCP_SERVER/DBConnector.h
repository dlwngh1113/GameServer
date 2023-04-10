#pragma once

class DBConnector
{
	SQLHENV m_henv;
	SQLHDBC m_hdbc;
	SQLHSTMT m_hstmt;
	int m_nParamIndex{ 0 };

	SQLSMALLINT m_nLenth;
	SQLINTEGER m_nRecord, m_nNative;
	SQLWCHAR m_sState[7], m_sMessage[UCHAR_MAX];

	SQLWCHAR* m_query{ nullptr };

private:
	void Release();
	void CheckError();

	DBConnector();
public:
	explicit DBConnector(const char* query);
	virtual ~DBConnector();

	void SetQueryString(const char* statement);
	SQLHSTMT& GetStatement() { return m_hstmt; }

	void ExecuteDirectSQL();
	void PrepareStatement();
	void ExecutePreparedStatement();

	void AddParameter(int val);
	void AddParameter(short val);
	void AddParameter(const char* val);
};