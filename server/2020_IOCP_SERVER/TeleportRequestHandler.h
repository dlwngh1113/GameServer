#pragma once
#include "LoginRequiredRequestHandler.h"

class TeleportRequestHandler : public LoginRequiredRequestHandler
{
public:
	virtual void HandleInGame();
	virtual std::shared_ptr<BaseRequestHandler> Create();
};