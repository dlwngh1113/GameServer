#pragma once
#include "Singleton.h"

namespace Core
{
	class DataBase : public Singleton<DataBase>
	{
		sql::Driver* m_driver;
		std::vector<std::unique_ptr<sql::Connection>> m_connections;
		int m_connectionIndex;

	public:
		DataBase();

	private:
		void Migrate();

	public:
		void Initialize();
		sql::Connection* GetConnection();
	};
}
