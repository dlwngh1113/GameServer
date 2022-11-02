#include "stdafx.h"
#include "RequestHandler.h"

void RequestHandler::Handle()
{
}

void RequestHandler::Init(ClientPeer* peer, BasePacket* packet)
{
	m_peer = peer;
	m_packet = packet;
}
