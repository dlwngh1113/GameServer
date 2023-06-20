#pragma once

class DBConnection
{
private:
	sql::Connection* m_connection;

public:
	DBConnection(sql::Connection* conn);
	virtual ~DBConnection();

	void SetConnection(sql::Connection* conn) { m_connection = conn; }
	sql::Connection* GetConnection() { return m_connection; }
};

