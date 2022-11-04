#pragma once
#include"BasePacket.h"

#pragma pack(push, 1)

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

#pragma pack(pop)