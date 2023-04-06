#pragma once

class Peer;
struct ClientCommon::BasePacket;

class BaseRequestHandler
{
protected:
	Peer* m_peer;
	ClientCommon::BasePacket* m_packet;
public:
	void Init(Peer* peer, ClientCommon::BasePacket* packet);

	virtual void Handle() = 0;
	virtual BaseRequestHandler* Create() = 0;
};