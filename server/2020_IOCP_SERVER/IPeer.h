#pragma once
#include"BasePacket.h"
class IPeer
{
public:
	virtual void ProcessPacket(BasePacket* packet) = 0;
};

