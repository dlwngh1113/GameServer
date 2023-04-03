#pragma once

class Peer;
class BasePacket;

class BaseRequestHandler
{
protected:
	Peer* m_peer;
	BasePacket* m_packet;
public:
	void Init(Peer* peer, BasePacket* packet);

	virtual void Handle() = 0;
	virtual BaseRequestHandler* Create() = 0;
};