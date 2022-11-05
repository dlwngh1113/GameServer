#pragma once
#include"Packets.h"
#include"RequestHandler.h"

class TeleportRequestHandler : public RequestHandler
{
public:
	virtual void HandleRequest();
	virtual RequestHandler* Create();
};

