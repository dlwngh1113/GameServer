#include "stdafx.h"
#include "BaseRequestHandler.h"
#include "Peer.h"

BaseRequestHandler::BaseRequestHandler()
	: m_packet{ nullptr }
	, m_peer{ nullptr }
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
