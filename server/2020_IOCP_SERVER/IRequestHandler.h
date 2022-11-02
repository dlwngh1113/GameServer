#pragma once
#include"ClientPeer.h"

class IRequestHandler
{
protected:
	ClientPeer* m_peer;
	BasePacket* m_packet;
public:
	virtual void Handle() = 0;
	virtual void Init(ClientPeer* peer, BasePacket* packet);
};
