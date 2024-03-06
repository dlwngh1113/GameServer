#include "stdafx.h"
#include "Logger.h"

void Logger::Log(const char* message)
{
	Log(message);
}

void Logger::Log(const string& message)
{
	m_messages.push(message);
}