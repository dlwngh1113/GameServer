#include "pch.h"
#include "BaseHandler.h"

void BaseHandler::Initialize(unsigned char* packet, short packetSize)
{
	m_packet = packet;
	m_packetSize = packetSize;
}
