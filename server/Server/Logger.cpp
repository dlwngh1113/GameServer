#include "stdafx.h"
#include "Logger.h"
#include "BaseApplication.h"

Logger Logger::s_instance;

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

template<typename... T>
void Logger::Log(const std::format_string<T...> fmt, T&&... args)
{

	m_messages.push(std::format(fmt, args));
}

template<>
std::string Logger::vformat(const std::string_view fmt, const std::format_args args)
{
	std::string str;
	str.reserve(fmt.size() + args._Estimate_required_capacity());
	vformat_to(std::back_insert_iterator{ str }, fmt, args);
	return str;
}
