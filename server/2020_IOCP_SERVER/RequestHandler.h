#pragma once
#include"BaseRequestHandler.h"

class RequestHandler : public BaseRequestHandler
{
public:
	virtual void HandleRequest() override;
	virtual BaseRequestHandler* Create() = 0;
};