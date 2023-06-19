#pragma once

class DBConnection
{
private:
	sql::Connection* conn;

public:
	DBConnection();
	virtual ~DBConnection();
};

