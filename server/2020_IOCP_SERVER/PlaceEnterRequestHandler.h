#pragma once
#include "Packets.h"
#include "RequestHandler.h"

class PlaceEnterRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	BaseRequestHandler* Create() override;
};

