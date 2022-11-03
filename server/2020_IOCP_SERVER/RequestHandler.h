#pragma once
#include"BasePacket.h"

class ClientPeer;

class RequestHandler
{
protected:
	ClientPeer* m_peer;
	BasePacket* m_packet;
public:
	void Handle();
	virtual void Init(ClientPeer* peer, BasePacket* packet);

	virtual void HandleRequest() = 0;
	virtual RequestHandler* Create() = 0;
};

