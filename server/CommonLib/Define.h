#pragma once

#ifdef _WIN32
	#ifdef COMMON_LIB_EXPORTS
		#define COMMON_LIB_API __declspec(dllexport)
	#else
		#define COMMON_LIB_API __declspec(dllimport)
	#endif
#endif

enum class Command : uint16_t
{
	Chatting,
	Move,
	Login,
	Teleport
};

enum class Event : uint16_t
{
	Chatting = UINT8_MAX,
	Move,
	Login,
	Teleport
};