#pragma once

namespace ClientFramework
{
	class Time
	{
	private:
		std::chrono::steady_clock::time_point m_prevUpdateTime;
		float m_deltaTime;

	public:
		Time();

	public:
		void UpdateFrame();
		float deltaTime() const { return m_deltaTime; }

		// Static Member Variables
	private:
		static Time s_instance;

		// Static Member Functions
	public:
		static Time& instance() { return s_instance; }
	};
}
