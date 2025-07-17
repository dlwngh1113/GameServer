#include "pch.h"
#include "BaseHandler.h"

void BaseHandler::Initialize(const uint8_t* packet, int16_t packetSize)
{
	m_packetSize = packetSize;
	memcpy_s(m_packet, m_packetSize, packet, m_packetSize);
}
