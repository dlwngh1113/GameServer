#pragma once
#include"BaseRequestHandler.h"

class RequestHandler : public BaseRequestHandler
{
public:
	virtual void HandleRequest() = 0;
	virtual BaseRequestHandler* Create() = 0;
};