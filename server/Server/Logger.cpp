#include "stdafx.h"
#include "Logger.h"
#include "BaseApplication.h"

Logger::Logger()
	: m_thread([this]() { LogOnConsole(); })
{
}

Logger::~Logger()
{
	m_thread.join();
}

void Logger::LogOnConsole()
{
	while (true)
	{
		std::string message;
		if (m_messages.try_pop(message))
			std::cerr << message << std::endl;
	}
}

void Logger::Log(const char* message)
{
	m_messages.push(message);
}

void Logger::Log(const std::string& message)
{
	m_messages.push(message);
}
