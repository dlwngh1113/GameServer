#pragma once
#include"BasePacket.h"
#include"Peer.h"

class RequestHandler
{
protected:
	Peer* m_peer;
	BasePacket* m_packet;
public:
	void Handle();
	void Init(Peer* peer, BasePacket* packet);

	virtual void HandleRequest() = 0;
	virtual RequestHandler* Create() = 0;
};