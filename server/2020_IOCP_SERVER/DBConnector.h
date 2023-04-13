#pragma once

class DBConnector
{
private:
	static DBConnector* s_instance;
	sql::Driver* m_driver;
	sql::Connection* m_connection;

	DBConnector();
public:
	virtual ~DBConnector();

	sql::Statement* GetStatement();
	sql::PreparedStatement* GetPreparedStatement(const char* sSql);

	static DBConnector* GetInstance()
	{
		if (!s_instance)
		{
			s_instance = new DBConnector();
		}

		return s_instance;
	}
};