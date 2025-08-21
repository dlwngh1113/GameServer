#include "pch.h"
#include "BaseHandler.h"

BaseHandler::~BaseHandler()
{
	if (m_packet)
	{
		delete[] m_packet;
		m_packet = nullptr;
	}
}

void BaseHandler::Initialize(const uint8_t* packet, int16_t packetSize)
{
	m_packetSize = packetSize;
	m_packet = new uint8_t[m_packetSize];
	memcpy_s(m_packet, m_packetSize, packet, m_packetSize);
}
