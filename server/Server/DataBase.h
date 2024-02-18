#pragma once

namespace Core
{
	class DataBase final
	{
		sql::Driver* m_driver;
		vector<unique_ptr<sql::Connection>> m_connections;

	public:
		DataBase();

	public:
		void Initialize();

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
