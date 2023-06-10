#pragma once

//
constexpr int WORLD_WIDTH = 800;
constexpr int WORLD_HEIGHT = 800;
constexpr int TILE_SIZE = 64;

constexpr int MAX_STR_LEN = 100;
constexpr int MAX_ID_LEN = 10;

// 서버 세팅
constexpr int MAX_USER = 10000;
constexpr int SERVER_PORT = 3500;
constexpr int  KEY_SERVER = 1000000;

constexpr int NUM_NPC = 10'000;
constexpr int MAX_THREAD_COUNT = 6;

// IO 세팅
constexpr char OP_MODE_RECV = 0;
constexpr char OP_MODE_SEND = 1;
constexpr char OP_MODE_ACCEPT = 2;

constexpr int MAX_BUFFER = 4096;
constexpr int MIN_BUFFER = 1024;

//
constexpr char MV_RIGHT = 0;
constexpr char MV_LEFT = 1;
constexpr char MV_DOWN = 2;
constexpr char MV_UP = 3;

enum class ServerEvent : short
{
	LoginOk = 0,
	LoginFail,
	UserMove,
	UserEnter,
	UserExit,
	UserChatting,
	StatusChanged,
};

enum class ClientCommand : short
{
	Login = 0,
	Logout,
	Move,
	Attack,
	ChattingMessageSend,
	Teleport,
	PlaceEnter,
};

namespace ClientCommon
{
#pragma pack(push, 1)

	struct Header
	{
		short type;
		short size;
	};

	struct BasePacket
	{
		Header header;
	};

#pragma region Login

	struct LoginRequest : BasePacket
	{
		char  name[MAX_ID_LEN];
	};

	struct LoginResponse : BasePacket
	{
		int  id;
		short hp;
		short level;
		int   exp;
		short x, y;
		int placeId;
	};

	struct LoginFailResponse : BasePacket
	{
		int	  id;
		char  message[MAX_STR_LEN];
	};

#pragma endregion

#pragma region Logout

	struct LogoutRequest : BasePacket
	{
	};

#pragma endregion

#pragma region Chatting

	struct ChattingRequest : BasePacket
	{
		char  message[MAX_STR_LEN];
	};

	struct ChattingEvent : BasePacket
	{
		int	  id;
		char  message[MAX_STR_LEN];
	};

#pragma endregion

#pragma region StatusChange

	struct StatusChangedEvent : BasePacket
	{
		int  id;
		short hp;
		short level;
		int   exp;
		char message[MAX_STR_LEN];
	};

#pragma endregion

#pragma region Move

	struct MoveRequest : BasePacket
	{
		char  direction;
		int	  move_time;
	};

	struct MoveResponse : BasePacket
	{
		int id;
		short x, y;
		int move_time;
	};

	struct UserMoveEvent : BasePacket
	{
		int id;
		short x, y;
	};

	struct TeleportRequest : BasePacket
	{
		short x, y;
	};

	struct TeleportResponse : BasePacket
	{
	};

#pragma endregion

#pragma region Place

	struct SPlace
	{
	};

	struct PlaceEnterRequest : BasePacket
	{
		int placeId;
	};

	struct PlaceEnterResponse : BasePacket
	{
		int id;
		short x, y;
		SPlace placeInfo;
	};

	struct UserEnterEvent : BasePacket
	{
		int  id;
		char name[MAX_ID_LEN];
		short x, y;
	};

	struct UserExitEvent : BasePacket
	{
		int  id;
	};

#pragma endregion

#pragma region Attack

	struct AttackRequest : BasePacket
	{
		int atkTime;
	};

#pragma endregion

#pragma pack(pop)
}