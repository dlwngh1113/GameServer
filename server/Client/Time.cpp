#include "pch.h"
#include "Time.h"

namespace ClientFramework
{
	Time Time::s_instance;

	Time::Time()
		: m_prevUpdateTime(std::chrono::high_resolution_clock::now())
		, m_deltaTime(0)
	{
	}

	void Time::UpdateFrame()
	{
		auto currentTime{ std::chrono::high_resolution_clock::now() };
		auto duration = currentTime - m_prevUpdateTime;
		m_prevUpdateTime = currentTime;

		m_deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / (float)std::micro::den;
	}
}