#pragma once
#include "Peer.h"

class ClientPeer
{
protected:
	Peer* m_peer;
public:
	explicit ClientPeer(Peer* peer, BaseRequestHandlerFactory* instance);
	virtual ~ClientPeer();

	int GetID() const { return m_peer->GetID(); }

	void SendPacket(ClientCommon::BasePacket* packet);
};