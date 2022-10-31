#pragma once
#include"stdafx.h"

class Logger
{
public:
	static void Error(std::string message);
	static void Info(std::string message);
};