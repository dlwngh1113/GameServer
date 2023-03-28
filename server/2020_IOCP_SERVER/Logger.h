#pragma once
#include"stdafx.h"

#define Log(fmt, ...) Logger::Info(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

class Logger
{
	static HANDLE s_ConsoleHandle;
public:
	static void Error(std::string message);
	static void Info(const char* file, const char* func, const char* line, const char* fmt, ...);
};