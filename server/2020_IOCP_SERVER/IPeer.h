#pragma once
class IPeer
{
public:
	virtual void ProcessPacket(unsigned char size, unsigned char* data) = 0;
	virtual void SendPacket(unsigned char* data, unsigned short snSize) = 0;
};

