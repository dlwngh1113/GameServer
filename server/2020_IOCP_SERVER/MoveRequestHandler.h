#pragma once
#include"Packets.h"
#include"RequestHandler.h"

class MoveRequestHandler : public RequestHandler
{
public:
	virtual void HandleRequest()  override;
	virtual BaseRequestHandler* Create() override;
};