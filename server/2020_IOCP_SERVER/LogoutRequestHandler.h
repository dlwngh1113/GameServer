#pragma once
#include"RequestHandler.h"

class LogoutRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	BaseRequestHandler* Create() override;
};

