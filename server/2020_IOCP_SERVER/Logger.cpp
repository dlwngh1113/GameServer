#include"stdafx.h"
#include "Logger.h"

HANDLE Logger::s_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Error(std::string message)
{
	SetConsoleTextAttribute(s_ConsoleHandle, 12);

	std::cout << "[Error] : " << message << std::endl;
}

void Logger::Info(std::string message)
{
	SetConsoleTextAttribute(s_ConsoleHandle, 15);

	std::cout << "[Info] : " << message << std::endl;
}
