#pragma once
#include "Singleton.h"

namespace Core
{
	class DataBase : public Singleton<DataBase>
	{
		sql::Driver* m_driver;
		std::vector<std::pair<std::unique_ptr<sql::Connection>, std::thread::id>> m_connections;

	public:
		DataBase();

	private:
		void Migrate();

	public:
		void Initialize();
		sql::Connection* GetConnection();
	};
}
