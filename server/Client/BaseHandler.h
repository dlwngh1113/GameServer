#pragma once

class BaseHandler
{
protected:
	uint8_t* m_packet;
	int16_t m_packetSize;

public:
	virtual ~BaseHandler();

	void Initialize(const uint8_t* packet, int16_t packetSize);
	virtual void Handle() = 0;
};