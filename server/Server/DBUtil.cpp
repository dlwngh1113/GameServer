#include "stdafx.h"
#include "DBUtil.h"
#include "DataBase.h"
#include "Logger.h"

std::shared_ptr<sql::ResultSet> DBUtil::GetUser(const std::string& id, const std::string& password)
{
	try
	{
		sql::Connection* con = Core::DataBase::instance().GetConnection();
		//std::unique_ptr<sql::PreparedStatement> stmt(Core::DataBase::instance().GetConnection()->prepareStatement("CALL GetUser(?,?)"));
		std::unique_ptr<sql::PreparedStatement> stmt(con->prepareStatement("CALL GetUser(?,?)"));
		stmt->setString(1, id);
		stmt->setString(2, password);

		std::shared_ptr<sql::ResultSet> result(stmt->executeQuery());
		delete con;
		if (result->next())
			return result;

		return nullptr;
	}
	catch (sql::SQLException& ex)
	{
		Logger::instance().Log(ex.getSQLState());
		return nullptr;
	}
}
