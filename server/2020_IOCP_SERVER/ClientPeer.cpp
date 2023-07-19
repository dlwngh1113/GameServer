#include "stdafx.h"
#include "ClientPeer.h"
#include "BaseRequestHandlerFactory.h"

ClientPeer::ClientPeer(Peer* peer, BaseRequestHandlerFactory* instance) : m_peer{peer}
{
	m_peer->Initialize(instance);
}

ClientPeer::~ClientPeer()
{
}

void ClientPeer::SendPacket(ClientCommon::BasePacket* packet)
{
	m_peer->SendPacket(packet);
}
