#pragma once
#include"framework.h"
#pragma pack(push, 1)

struct BasePacket
{
	unsigned char size;
	unsigned char type;
};

#pragma pack(pop)