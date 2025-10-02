#include "stdafx.h"
#include "PacketWork.h"

namespace Core
{
	PacketWork::PacketWork()
		: IWork{}
	{
	}
	
	PacketWork::~PacketWork()
	{
	}

	PacketWork::PacketWork(std::function<void()> func)
		: IWork{}
	{
		m_handler = func;
	}

	void PacketWork::Execute()
	{
		if (m_handler)
		{
			m_handler();
		}
	}
}