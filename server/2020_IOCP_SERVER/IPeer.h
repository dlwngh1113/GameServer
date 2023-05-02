#pragma once
class IPeer
{
	virtual void ProcessPacket(unsigned char size, unsigned char* data) = 0;
public:
	virtual void ProcessIO(DWORD ioSize) = 0;
	virtual void SendPacket(unsigned char* data, unsigned short snSize) = 0;
};

