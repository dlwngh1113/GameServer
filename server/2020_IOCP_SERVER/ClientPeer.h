#pragma once
#include"Peer.h"

class ClientPeer
{
protected:
	Peer* m_peer;
public:
	ClientPeer(Peer* peer, IFactory* instance);
	virtual ~ClientPeer();

	int GetID() const { return m_peer->GetID(); }
};