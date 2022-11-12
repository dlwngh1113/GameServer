#pragma once
#include"Packets.h"
#include "RequestHandler.h"

class LoginRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	BaseRequestHandler* Create() override;
};