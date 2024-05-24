#pragma once
#include "Singleton.h"

namespace ClientFramework
{
	class Time : public Singleton<Time>
	{
	private:
		std::chrono::steady_clock::time_point m_prevUpdateTime;
		float m_deltaTime;

	public:
		Time();

	public:
		void UpdateFrame();
		float deltaTime() const { return m_deltaTime; }
	};
}
