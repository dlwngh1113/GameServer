#pragma once
#include "BaseRequestHandler.h"

class User;

class RequestHandler : public Core::BaseRequestHandler
{
public:
	void Handle() override final;
	virtual void HandleRequest() = 0;
};
