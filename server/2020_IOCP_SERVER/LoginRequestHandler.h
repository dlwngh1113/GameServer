#pragma once
#include"Packets.h"
#include "RequestHandler.h"

class LoginRequestHandler : public RequestHandler
{
public:
	void Init(ClientPeer* peer, BasePacket* packet) override;

	void HandleRequest() override;
	RequestHandler* Create() override;
};