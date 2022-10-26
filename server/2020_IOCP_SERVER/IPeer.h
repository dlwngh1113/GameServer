#pragma once
class IPeer
{
public:
	virtual void ProcessPacket(unsigned char size, unsigned char* data) = 0;
};

