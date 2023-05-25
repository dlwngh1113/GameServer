#pragma once
#include "LoginRequiredRequestHandler.h"

class PlaceEnterRequestHandler : public LoginRequiredRequestHandler
{
public:
	void HandleInGame() override;
	std::shared_ptr<BaseRequestHandler> Create() override;
};

