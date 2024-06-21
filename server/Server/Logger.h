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
	template<typename... T>
	void Log(const std::format_string<T...> fmt, T&&... args);

	template <int = 0>
	std::string vformat(const std::string_view fmt, const std::format_args args);

private:
	void LogOnConsole();

	// Static member variables
private:
	static Logger s_instance;

	// Static member functions
public:
	static Logger& instance() { return s_instance; }
};
