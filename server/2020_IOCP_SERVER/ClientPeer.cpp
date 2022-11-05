#include"stdafx.h"
#include "ClientPeer.h"

ClientPeer::ClientPeer(Peer* peer, IFactory* instance) : m_peer{peer}
{
	m_peer->Init(instance);
}

ClientPeer::~ClientPeer()
{
	delete m_peer;
}
