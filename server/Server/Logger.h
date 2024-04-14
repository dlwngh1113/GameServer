#pragma once

class Logger
{
private:
	concurrency::concurrent_queue<std::string> m_messages;

public:
	Logger();

public:
	void Log(const char* message);
	void Log(const std::string& message);

	// Static member variables
private:
	static Logger s_instance;

	// Static member functions
public:
	static Logger& instance() { return s_instance; }
};
