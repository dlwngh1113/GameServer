#include "stdafx.h"
#include "BaseRequestHandler.h"
#include "Peer.h"

BaseRequestHandler::BaseRequestHandler()
{
}

BaseRequestHandler::~BaseRequestHandler()
{
}

void BaseRequestHandler::Initialize(Peer* peer, ClientCommon::BasePacket* packet)
{
	m_peer = peer;
	m_packet = packet;
}
