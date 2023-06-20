#pragma once

class DBConnection
{
private:
	sql::Connection* m_connection;

public:
	DBConnection(sql::Connection*& conn);
	virtual ~DBConnection();

	sql::Connection* operator->() override;
};

