#pragma once
#include"BasePacket.h"
#include"IRequestHandler.h"
#include"ClientPeer.h"

class RequestHandler : public IRequestHandler
{
protected:
	ClientPeer* m_peer;
	BasePacket* m_packet;
public:
	virtual void Handle();
	virtual void Init(ClientPeer* peer, BasePacket* packet);
};

