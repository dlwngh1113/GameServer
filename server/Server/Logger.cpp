#include "stdafx.h"
#include "Logger.h"

HANDLE Logger::s_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Error(wstring message)
{
	SetConsoleTextAttribute(s_ConsoleHandle, 12);

	wcout << "[Error] : " << message << endl;
}

void Logger::Info(const char* fmt, ...)
{
	SetConsoleTextAttribute(s_ConsoleHandle, 15);

	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
}
