#pragma once

class Peer;
struct ClientCommon::BasePacket;

class BaseRequestHandler
{
protected:
	std::shared_ptr<Peer> m_peer;
	ClientCommon::BasePacket* m_packet;
public:
	BaseRequestHandler() = delete;
	virtual ~BaseRequestHandler();

	void Initialize(std::shared_ptr<Peer> peer, ClientCommon::BasePacket* packet);

	virtual void Handle() = 0;
	virtual BaseRequestHandler* Create() = 0;
};