#pragma once
#include "IRequestHandler.h"
#include"Packets.h"
#include"Logger.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	void HandleRequest(BasePacket* packet) override;
};