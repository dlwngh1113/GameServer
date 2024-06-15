#pragma once
#include "BaseCommandHandler.h"

class CommandHandler : public Core::BaseCommandHandler
{
public:
	void Handle() override final;

protected:
	virtual void HandleRequest() = 0;
};
