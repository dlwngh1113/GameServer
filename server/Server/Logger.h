#pragma once

#define LogFormat(fmt, ...) Logger::Info(fmt, ##__VA_ARGS__)
#define Log(arg) wcout << arg << endl;

class Logger
{
	static HANDLE s_ConsoleHandle;
public:
	static void Error(wstring message);
	static void Info(const char* fmt, ...);
};