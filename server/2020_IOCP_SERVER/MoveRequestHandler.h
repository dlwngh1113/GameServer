#pragma once
#include "LoginRequiredRequestHandler.h"

class MoveRequestHandler : public LoginRequiredRequestHandler
{
public:
	virtual void HandleInGame()  override;
};