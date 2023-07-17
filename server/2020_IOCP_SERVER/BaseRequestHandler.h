#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerException.h"

class Peer;
struct ClientCommon::BasePacket;

class BaseRequestHandler : public IRequestHandler
{
protected:
	Peer* m_peer;
	ClientCommon::BasePacket* m_packet;
public:
	BaseRequestHandler();
	virtual ~BaseRequestHandler();

	void Initialize(Peer* peer, ClientCommon::BasePacket* packet);

	virtual void Handle() = 0;
	virtual std::shared_ptr<BaseRequestHandler> Create() = 0;
};