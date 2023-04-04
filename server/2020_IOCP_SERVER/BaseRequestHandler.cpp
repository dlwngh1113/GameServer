#include "stdafx.h"
#include "BaseRequestHandler.h"
#include "Peer.h"

void BaseRequestHandler::Init(Peer* peer, BasePacket* packet)
{
	m_peer = peer;
	m_packet = packet;
}
