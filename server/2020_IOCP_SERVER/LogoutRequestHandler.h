#pragma once
#include"Packets.h"
#include"RequestHandler.h"

class LogoutRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	LogoutRequestHandler* Create() override;
};

