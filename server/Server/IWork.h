#pragma once

namespace Core
{
	class IWork
	{
	public:
		IWork() {}
		virtual ~IWork() {}
		virtual void Execute() = 0;
	};
}
