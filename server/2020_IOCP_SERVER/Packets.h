#pragma once
#include"BasePacket.h"

#pragma pack(push, 1)

struct LoginPacket : BasePacket
{
	char  name[MAX_ID_LEN];
};

#pragma pack(pop)