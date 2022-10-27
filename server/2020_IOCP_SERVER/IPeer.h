#pragma once
#include"BasePacket.h"
class IPeer
{
public:
	virtual void ProcessPacket(unsigned char size, unsigned char* data) = 0;
	virtual void ProcessPacket(BasePacket* packet) = 0;
};

