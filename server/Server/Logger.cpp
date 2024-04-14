#include "stdafx.h"
#include "Logger.h"
#include "BaseApplication.h"

Logger Logger::s_instance;

Logger::Logger()
{
	boost::asio::dispatch(Core::BaseApplication::threads(), [this]() {
		while (true)
		{
			std::string message;
			if (m_messages.try_pop(message))
				std::cerr << message << std::endl;
		}
		});
}

void Logger::Log(const char* message)
{
	m_messages.push(message);
}

void Logger::Log(const std::string& message)
{
	m_messages.push(message);
}