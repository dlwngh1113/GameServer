#pragma once
#pragma pack(push, 1)

struct BasePacket
{
	unsigned char size;
	unsigned char type;
};

#pragma pack(pop)