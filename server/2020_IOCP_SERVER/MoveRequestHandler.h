#pragma once
#include"RequestHandler.h"

class MoveRequestHandler : public RequestHandler
{
public:
	virtual void HandleRequest()  override;
	virtual BaseRequestHandler* Create() override;
};