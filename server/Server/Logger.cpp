#include "stdafx.h"
#include "Logger.h"
#include "BaseApplication.h"

Logger Logger::s_instance;

Logger::Logger()
{
	boost::asio::dispatch(Core::BaseApplication::threads(), [this]() {
		while (true)
		{
			string message;
			if (m_messages.try_pop(message))
				cerr << message << endl;
		}
		});
}

void Logger::Log(const char* message)
{
	m_messages.push(message);
}

void Logger::Log(const string& message)
{
	m_messages.push(message);
}