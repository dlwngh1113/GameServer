#include "Logger.h"

void Logger::Error(std::string message)
{
	std::cout << "Error : " << message << std::endl;
}

void Logger::Info(std::string message)
{
	std::cout << "Info : " << message << std::endl;
}
