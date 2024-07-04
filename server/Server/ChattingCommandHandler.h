#pragma once
#include "LoginRequiredHandler.h"

class ChattingCommandHandler : public LoginRequiredHandler
{
protected:
	virtual void HandleCommand() override;
};
