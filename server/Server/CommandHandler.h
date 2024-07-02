#pragma once
#include "BaseCommandHandler.h"

class CommandHandler : public Core::BaseCommandHandler
{
public:
	void Handle() = 0;
};
