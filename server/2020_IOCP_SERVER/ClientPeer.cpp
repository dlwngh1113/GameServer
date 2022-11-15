#include"stdafx.h"
#include "ClientPeer.h"

ClientPeer::ClientPeer(Peer* peer, IHandlerFactory* instance) : m_peer{peer}
{
	m_peer->Init(instance);
}

ClientPeer::~ClientPeer()
{
	delete m_peer;
}
