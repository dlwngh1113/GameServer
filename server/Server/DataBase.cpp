#include "stdafx.h"
#include "DataBase.h"
#include "Logger.h"

namespace Core
{
	namespace
	{
		static constexpr char kHostAddress[] = "127.0.0.1:3306";
		static constexpr char kUserName[] = "root";
		static constexpr char kPassword[] = "ljh915727!";
		static constexpr char kSchema[] = "dnd";
	}

	DataBase::DataBase()
		: m_driver(get_driver_instance())
	{
	}

	void DataBase::Initialize()
	{
		Logger::instance().Log("Database Initialize Started!");
		Migrate();
		Logger::instance().Log("Database Initialize finished!");
	}

	std::unique_ptr<sql::Connection> DataBase::GetConnection()
	{
		std::unique_ptr<sql::Connection> conn(m_driver->connect(kHostAddress, kUserName, kPassword));
		conn->setSchema(kSchema);
		return conn;
	}

	void DataBase::Migrate()
	{
		Logger::instance().Log("Database Migration Started!");

		auto connection = GetConnection();

		try
		{
			// Begin transaction
			connection->setAutoCommit(false);

			std::unique_ptr<sql::Statement> statement(connection->createStatement());

			statement->execute("CREATE TABLE IF NOT EXISTS `t_User`(`id` VARCHAR(12) PRIMARY KEY NOT NULL, `password` \
				VARCHAR(128) NOT NULL, `x` FLOAT DEFAULT 0, `y` FLOAT DEFAULT 0); ");

			// Commit transaction
			connection->commit();
		}
		catch (sql::SQLException& ex)
		{
			Logger::instance().Log(format("SQLException: {}\nSQLState: {}\nErrorCode: {}", ex.what(), ex.getSQLState(), ex.getErrorCode()));
		}

		Logger::instance().Log("Database Migration Started!");
	}
}