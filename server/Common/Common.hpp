#pragma once

//
constexpr int MAX_STR_LEN = 100;
constexpr int MAX_ID_LEN = 10;

// 서버 세팅
constexpr int MAX_USER = 10000;
constexpr int SERVER_PORT = 3500;
constexpr int  KEY_SERVER = 1000000;

constexpr int NUM_NPC = 10'000;
constexpr int MAX_THREAD_COUNT = 6;

// IO 세팅
constexpr int MAX_BUFFER = 4096;
constexpr int MIN_BUFFER = 1024;

//
constexpr char MV_RIGHT = 0;
constexpr char MV_LEFT = 1;
constexpr char MV_DOWN = 2;
constexpr char MV_UP = 3;

enum class ServerEvent : short
{
};

enum class ClientCommand : short
{
};

namespace ClientCommon
{
#pragma pack(push, 1)

	struct Header
	{
		short type;
		short size;
	};
#pragma pack(pop)
}