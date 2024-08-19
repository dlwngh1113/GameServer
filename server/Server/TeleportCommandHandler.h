#pragma once
#include "LoginRequiredHandler.h"

class TeleportCommandHandler : public LoginRequiredHandler
{
protected:
	virtual void HandleCommand() override;
};

