#pragma once
#include "CommandHandler.h"

class ChattingCommandHandler : public CommandHandler
{
protected:
	virtual void HandleRequest() override;
};
