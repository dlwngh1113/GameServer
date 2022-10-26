#pragma once
class BasePacket
{
public:
	unsigned char size;
	unsigned char type;
	unsigned char* data;
};