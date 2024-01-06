#pragma once
#include "RequestHandler.h"

class LoginRequiredRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override final;
	virtual void HandleInGame() = 0;
};

