#include "stdafx.h"
#include "RequestHandler.h"
#include"ClientPeer.h"

void RequestHandler::Handle()
{
	HandleRequest();
}

void RequestHandler::HandleRequest()
{
}

void RequestHandler::Init(ClientPeer* peer, BasePacket* packet)
{
	m_peer = peer;
	m_packet = packet;
}
