#include "stdafx.h"
#include "ClientPeer.h"

ClientPeer::ClientPeer(Peer* peer, IHandlerFactory* instance) : m_peer{peer}
{
	m_peer->Initialize(instance);
}

ClientPeer::~ClientPeer()
{
	if (m_peer)
		delete m_peer;
}

void ClientPeer::SendPacket(ClientCommon::BasePacket* packet)
{
	m_peer->SendPacket(packet);
}
