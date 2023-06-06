#include "pch.h"
#include "Handler.h"

Handler::Handler()
{
}

Handler::~Handler()
{
}

void Handler::Init(unsigned char* packet, short snPacketSize)
{
	m_packet = packet;
	m_snPacketSize = snPacketSize;
}
