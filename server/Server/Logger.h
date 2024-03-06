#pragma once

class Logger
{
private:
	queue<string> m_messages;

public:
	void Log(const char* message);
	void Log(const string& message);

	// Static member variables
private:
	static Logger s_instance;

	// Static member functions
public:
	static Logger& instance() { return s_instance; }
};