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

#pragma pack(pop)