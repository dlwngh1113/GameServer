#include"stdafx.h"
#include "IRequestHandler.h"

void IRequestHandler::Init(ClientPeer* peer, BasePacket* packet)
{
	m_peer = peer;
	m_packet = packet;
}
