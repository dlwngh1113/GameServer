#pragma once

class Logger
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

	// Static member variables
private:
	static Logger s_instance;

	// Static member functions
public:
	static Logger& instance() { return s_instance; }
};
