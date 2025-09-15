#pragma once
#include "IWork.h"

namespace Core
{
	class PacketWork : public IWork
	{
		std::function<void()> m_handler;

	public:
		PacketWork();
		virtual ~PacketWork();
		PacketWork(std::function<void()> func);
		virtual void Execute() override;
	};
}
