#pragma once
#include"Packets.h"
#include"RequestHandler.h"

class MoveRequestHandler : public RequestHandler
{
public:
	virtual void Init(Peer* peer, BasePacket* packet) override;

	virtual void HandleRequest()  override;
	virtual RequestHandler* Create() override;
};