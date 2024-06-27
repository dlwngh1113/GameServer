#pragma once
#include "Singleton.h"

class Logger : public Core::Singleton<Logger>
{
private:
	concurrency::concurrent_queue<std::string> m_messages;
	std::thread m_thread;

public:
	Logger();
	virtual ~Logger();

public:
	void Log(const char* message);
	void Log(const std::string& message);

private:
	void LogOnConsole();
};
