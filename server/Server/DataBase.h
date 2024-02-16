#pragma once
#include "ObjectPool.h"

namespace Core
{
	class DataBase final
	{
		sql::Driver* m_driver;

	public:
		DataBase();
		
	};
}
