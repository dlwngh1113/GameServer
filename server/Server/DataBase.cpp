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

		for (int i = 0; i < MAX_THREAD_COUNT; ++i)
		{
			std::unique_ptr<sql::Connection> connection(m_driver->connect(kHostAddress, kUserName, kPassword));
			connection->setSchema(kSchema);
			m_connections.emplace_back(std::make_pair(std::move(connection), std::thread::id()));
		}

		Logger::instance().Log("Database Initialize finished!");

		Migrate();
	}

	sql::Connection* DataBase::GetConnection()
	{
		//int index = 0;
		//while (true) {
		//	std::pair<std::unique_ptr<sql::Connection>, std::thread::id>& pair(m_connections[index]);
		//	if (pair.second == std::thread::id() || pair.second == std::this_thread::get_id()) {
		//		pair.second = std::this_thread::get_id();
		//		return pair.first.get();
		//	}
		//	
		//	index = (index + 1) % m_connections.size();
		//}
		sql::Connection* conn = m_driver->connect(kHostAddress, kUserName, kPassword);
		conn->setSchema(kSchema);
		return conn;
	}

	void DataBase::Migrate()
	{
		Logger::instance().Log("Database Migration Started!");

		sql::Connection* connection = GetConnection();

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