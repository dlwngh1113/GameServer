#pragma once
#include "CommandHandler.h"

class LoginCommandHandler : public CommandHandler
{
protected:
	virtual void HandleRequest() override;
};
