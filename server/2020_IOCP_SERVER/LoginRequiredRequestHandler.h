#pragma once
#include "RequestHandler.h"

class LoginRequiredRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override final;
	virtual void HandleInGame() = 0;
	virtual std::shared_ptr<BaseRequestHandler> Create() = 0;
};

