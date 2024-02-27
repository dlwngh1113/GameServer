#pragma once

class Logger
{
	boost::log::sources::logger m_logger;

public:
	Logger();

	void Log(const char* message);
	void Log(const string& message);

private:
	static Logger s_instance;

public:
	static Logger& instance() { return s_instance; }
};