#include "pch.h"
#include "Time.h"

namespace ClientFramework
{
	Time Time::s_instance;

	Time::Time()
		: m_prevUpdateTime(chrono::high_resolution_clock::now())
		, m_deltaTime(0)
	{
	}

	void Time::UpdateFrame()
	{
		chrono::steady_clock::time_point currentTime{ chrono::high_resolution_clock::now() };
		auto duration = currentTime - m_prevUpdateTime;
		m_prevUpdateTime = currentTime;

		m_deltaTime = (float)chrono::duration_cast<chrono::microseconds>(duration).count() / (float)micro::den;
	}
}