#pragma once

#define LogFormat(fmt, ...) Logger::Info(fmt, ##__VA_ARGS__)
#define Log(arg) std::cout << arg << std::endl;

class Logger
{
	static HANDLE s_ConsoleHandle;
public:
	static void Error(std::string message);
	static void Info(const char* fmt, ...);
};