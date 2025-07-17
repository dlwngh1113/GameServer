#include "stdafx.h"
#include "DBUtil.h"
#include "DataBase.h"
#include "Logger.h"

std::shared_ptr<sql::ResultSet> DBUtil::GetUser(const std::string& id, const std::string& password)
{
	try
	{
		auto connection = Core::DataBase::instance().GetConnection();
		std::unique_ptr<sql::PreparedStatement> stmt(connection->prepareStatement("CALL GetUser(?,?)"));
		stmt->setString(1, id);
		stmt->setString(2, password);

		std::shared_ptr<sql::ResultSet> result(stmt->executeQuery());
		if (result->next())
			return result;
	}
	catch (sql::SQLException& ex)
	{
		Logger::instance().Log(ex.what());
	}

	return nullptr;
}
