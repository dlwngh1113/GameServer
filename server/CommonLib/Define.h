#pragma once

#ifdef _WIN32
	#ifdef COMMON_LIB_EXPORTS
		#define COMMON_LIB_API __declspec(dllexport)
	#else
		#define COMMON_LIB_API __declspec(dllimport)
	#endif
#endif

enum class Command : short
{
	Chatting,
	Move,
	Login,
	Teleport
};

enum class Event : short
{
	Chatting = -32767,
	Move = 1,
	Login,
	Teleport
};