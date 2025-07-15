#pragma once

#ifdef _WIN32
	#ifdef COMMON_LIB_EXPORTS
		#define COMMON_LIB_API __declspec(dllexport)
	#else
		#define COMMON_LIB_API __declspec(dllimport)
	#endif
#endif

enum class Command : int16_t
{
	Chatting,
	Move,
	Login,
	Teleport
};

enum class Event : int16_t
{
	Chatting = INT16_MIN,
	Move = 1,
	Login,
	Teleport
};