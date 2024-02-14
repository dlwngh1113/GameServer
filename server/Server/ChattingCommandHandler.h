#pragma once
#include "CommandHandler.h"

class ChattingCommandHandler : public CommandHandler
{
public:
	virtual void HandleRequest() override;
};
