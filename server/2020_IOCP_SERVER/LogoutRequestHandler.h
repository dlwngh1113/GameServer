#pragma once
#include "LoginRequiredRequestHandler.h"

class LogoutRequestHandler : public LoginRequiredRequestHandler
{
public:
	void HandleInGame() override;
};

