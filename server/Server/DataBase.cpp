#include "stdafx.h"
#include "DataBase.h"

namespace Core
{
	DataBase::DataBase()
		: m_driver(get_driver_instance())
	{
	}
}