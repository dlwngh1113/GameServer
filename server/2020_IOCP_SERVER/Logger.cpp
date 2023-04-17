#include "stdafx.h"
#include "Logger.h"

HANDLE Logger::s_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Error(std::string message)
{
	SetConsoleTextAttribute(s_ConsoleHandle, 12);

	std::cout << "[Error] : " << message << std::endl;
}

void Logger::Info(const char* file, const char* func, const int line, const char* fmt, ...)
{
	SetConsoleTextAttribute(s_ConsoleHandle, 15);

	va_list ap;
	va_start(ap, fmt);
	printf("[%s : %d] ", file, line);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
}
