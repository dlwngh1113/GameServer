#pragma once

class DBConnector
{
	static DBConnector* m_connector;
	static sql::Driver* m_driver;
	static sql::Connection* m_connection;
public:
	DBConnector();
	virtual ~DBConnector();

	sql::Statement* GetStatement();
	sql::PreparedStatement* GetPreparedStatement(const char* sSql);

	static DBConnector* GetInstance()
	{
		if (!m_connector)
			m_connector = new DBConnector();

		return m_connector;
	}
};