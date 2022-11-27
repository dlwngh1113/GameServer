#pragma once
#include"stdafx.h"

class Logger
{
	static HANDLE s_ConsoleHandle;
public:
	static void Error(std::string message);
	static void Info(std::string message);
};