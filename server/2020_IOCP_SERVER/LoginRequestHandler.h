#pragma once
#include"Packets.h"
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	void HandleRequest(BasePacket* packet) override;
};