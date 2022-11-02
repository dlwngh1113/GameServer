#pragma once
#include"Packets.h"
#include "RequestHandler.h"

class LoginRequestHandler : public RequestHandler
{
public:
	void Handle() override;
	void Init(ClientPeer* peer, BasePacket* packet) override;
};