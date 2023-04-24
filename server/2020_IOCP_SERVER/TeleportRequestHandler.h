#pragma once
#include "RequestHandler.h"

class TeleportRequestHandler : public RequestHandler
{
public:
	virtual void HandleRequest();
	virtual BaseRequestHandler* Create();
};