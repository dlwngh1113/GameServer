#include "stdafx.h"
#include "DataBase.h"

namespace Core
{
	DataBase DataBase::s_instance;
	namespace
	{
		static constexpr string kHostAddress("127.0.0.1:3306");
		static constexpr string kUserName("root");
		static constexpr string kPassword("ljh915727!");
		static constexpr string kSchema("dnd");
	}

	DataBase::DataBase()
		: m_driver(get_driver_instance())
		, m_connectionIndex(0)
	{
	}

	void DataBase::Initialize()
	{
		cerr << __FUNCTION__ << " Started\n";

		unique_ptr<sql::Connection> connection = nullptr;
		for (int i = 0; i < MAX_THREAD_COUNT; ++i)
		{
			connection.reset(m_driver->connect(kHostAddress, kUserName, kPassword));
			connection->setSchema(kSchema);
			m_connections.emplace_back(move(connection));
		}

		cerr << __FUNCTION__ << " Finished\n";

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
		cerr << __FUNCTION__ << " Started\n";

		sql::Connection* connection = GetConnection();

		try
		{
			// Begin transaction
			connection->setAutoCommit(false);

			unique_ptr<sql::Statement> statement = nullptr;
			statement.reset(connection->createStatement());

			statement->execute("CREATE TABLE IF NOT EXISTS `t_User`(`id` VARCHAR(36) PRIMARY KEY NOT NULL, `name` NVARCHAR(24) NOT NULL DEFAULT '');");

			// Commit transaction
			connection->commit();
		}
		catch (sql::SQLException& ex)
		{
			cerr << "SQLException: " << ex.what() << endl;
			cerr << "SQLState: " << ex.getSQLState() << endl;
			cerr << "ErrorCode: " << ex.getErrorCode() << endl;

			if (connection)
				connection->rollback();
		}

		cerr << __FUNCTION__ << " Finished\n";
	}
}