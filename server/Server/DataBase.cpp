#include "stdafx.h"
#include "DataBase.h"
#include "Logger.h"

namespace Core
{
	DataBase DataBase::s_instance;
	namespace
	{
		static constexpr std::string kHostAddress("127.0.0.1:3306");
		static constexpr std::string kUserName("root");
		static constexpr std::string kPassword("ljh915727!");
		static constexpr std::string kSchema("dnd");
	}

	DataBase::DataBase()
		: m_driver(get_driver_instance())
		, m_connectionIndex(0)
	{
	}

	void DataBase::Initialize()
	{
		Logger::instance().Log("Database Initialize Started!");

		std::unique_ptr<sql::Connection> connection = nullptr;
		for (int i = 0; i < MAX_THREAD_COUNT; ++i)
		{
			connection.reset(m_driver->connect(kHostAddress, kUserName, kPassword));
			connection->setSchema(kSchema);
			m_connections.emplace_back(std::move(connection));
		}

		Logger::instance().Log("Database Initialize finished!");

		Migrate();
	}

	sql::Connection* DataBase::GetConnection()
	{
		if (++m_connectionIndex == m_connections.size())
			m_connectionIndex = 0;

		return m_connections[m_connectionIndex].get();
	}

	void DataBase::Migrate()
	{
		Logger::instance().Log("Database Migration Started!");

		sql::Connection* connection = GetConnection();

		try
		{
			// Begin transaction
			connection->setAutoCommit(false);

			std::unique_ptr<sql::Statement> statement = nullptr;
			statement.reset(connection->createStatement());

			statement->execute("CREATE TABLE IF NOT EXISTS `t_User`(`id` VARCHAR(36) PRIMARY KEY NOT NULL, `name` NVARCHAR(24) NOT NULL DEFAULT '');");

			// Commit transaction
			connection->commit();
		}
		catch (sql::SQLException& ex)
		{
			Logger::instance().Log(format("SQLException: {}\nSQLState: {}\nErrorCode: {}", ex.what(), ex.getSQLState(), ex.getErrorCode()));

			if (connection)
				connection->rollback();
		}

		Logger::instance().Log("Database Migration Started!");
	}
}