#pragma once
#include "LoginRequiredHandler.h"

class MoveCommandHandler : public LoginRequiredHandler
{
protected:
	virtual void HandleCommand() override;
};

