#include "stdafx.h"
#include "ClientPeer.h"

ClientPeer::ClientPeer(Peer* peer, IHandlerFactory* instance) : m_peer{peer}
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
