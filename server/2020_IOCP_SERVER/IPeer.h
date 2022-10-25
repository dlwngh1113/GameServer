#pragma once
class IPeer
{
public:
	virtual void ProcessPacket(unsigned char size, unsigned char type) = 0;
};

