#pragma once

#include "RequestHandlerException.h"

class Peer;
struct ClientCommon::BasePacket;

class BaseRequestHandler
{
protected:
	std::shared_ptr<Peer> m_peer;
	ClientCommon::BasePacket* m_packet;
public:
	BaseRequestHandler();
	virtual ~BaseRequestHandler();

	void Initialize(std::shared_ptr<Peer> peer, ClientCommon::BasePacket* packet);

	virtual void Handle() = 0;
	virtual std::shared_ptr<BaseRequestHandler> Create() = 0;
};