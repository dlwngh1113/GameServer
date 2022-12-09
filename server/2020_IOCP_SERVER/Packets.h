#pragma once
#include"BasePacket.h"

#pragma pack(push, 1)

// 로그인

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

// 이동

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

struct TeleportRequest : BasePacket
{
	short x, y;
};

struct TeleportResponse : BasePacket
{
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

struct UserMoveEvent : BasePacket
{
	int id;
	short x, y;
};

#pragma pack(pop)