#pragma once

namespace Core
{
	class DataBase final
	{
		sql::Driver* m_driver;
		vector<unique_ptr<sql::Connection>> m_connections;
		int m_connectionIndex;

	public:
		DataBase();

	private:
		void Migrate();

	public:
		void Initialize();
		sql::Connection* GetConnection();

		//
		//
		//
		
	public:
		DataBase operator=(const DataBase& other) = delete;
		DataBase(const DataBase& other) = delete;

		// Static member variables
	private:
		static DataBase s_instance;

		// Static member functions
	public:
		static DataBase& instance() { return s_instance; }
	};
}
