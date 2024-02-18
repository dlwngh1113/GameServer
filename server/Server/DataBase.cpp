#include "stdafx.h"
#include "DataBase.h"

namespace Core
{
	DataBase::DataBase()
		: m_driver(get_driver_instance())
	{
	}

	void DataBase::Initialize()
	{
		cout << __FUNCTION__ << " Started\n" << endl;
		unique_ptr<sql::Connection> connection = nullptr;
		for (int i = 0; i < MAX_THREAD_COUNT; ++i)
		{
			connection = make_unique<sql::Connection>(m_driver->connect("127.0.0.1:3306", "root", "root"));
			m_connections.emplace_back(move(connection));
		}
		cout << __FUNCTION__ << " Finished\n" << endl;
	}
}