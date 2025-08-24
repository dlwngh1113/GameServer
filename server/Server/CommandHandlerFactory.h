#pragma once
#include "Singleton.h"
#include "BaseCommandHandlerFactory.h"

class CommandHandlerFactory: public Core::BaseCommandHandlerFactory, public Core::Singleton<CommandHandlerFactory>
{
public:
	CommandHandlerFactory();
	virtual ~CommandHandlerFactory();

	virtual void Initialize() override;
};
