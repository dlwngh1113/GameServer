#pragma once
#include "CommandHandler.h"

class MoveCommandHandler : public CommandHandler
{
protected:
	virtual void HandleRequest() override;
};

