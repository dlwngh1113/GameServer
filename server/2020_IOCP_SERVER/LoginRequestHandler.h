#pragma once
#include "RequestHandler.h"

class LoginRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	std::shared_ptr<BaseRequestHandler> Create() override;
};