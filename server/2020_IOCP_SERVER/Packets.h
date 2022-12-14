#pragma once
#include"BasePacket.h"
#include"Defines.h"

#pragma pack(push, 1)

#pragma region Login

struct LoginRequest : BasePacket
{
	char  name[MAX_ID_LEN];
};

struct LoginResponse : BasePacket
{
	int  id;
	short x, y;
	short hp;
	short level;
	int   exp;
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