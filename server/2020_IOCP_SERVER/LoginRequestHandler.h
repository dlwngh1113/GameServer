#pragma once
#include"Packets.h"
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	void Handle() override;
	void Init(ClientPeer* peer, BasePacket* packet) override;
};