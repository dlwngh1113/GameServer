#pragma once

class BaseHandler
{
protected:
	unsigned char* m_packet;
	short m_packetSize;

public:
	void Initialize(unsigned char* packet, short packetSize);
	virtual void Handle() = 0;
};