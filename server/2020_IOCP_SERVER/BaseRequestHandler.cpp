#include "stdafx.h"
#include "BaseRequestHandler.h"
#include "Peer.h"
#include "BasePacket.h"

void BaseRequestHandler::Init(Peer* peer, BasePacket* packet)
{
	m_peer = peer;
	m_packet = packet;
}
