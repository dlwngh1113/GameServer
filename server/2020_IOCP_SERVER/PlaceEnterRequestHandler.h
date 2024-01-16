#pragma once
#include "LoginRequiredRequestHandler.h"

class PlaceEnterRequestHandler : public LoginRequiredRequestHandler
{
public:
	void HandleInGame() override;
};

