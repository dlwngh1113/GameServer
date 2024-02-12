#pragma once
#include "BaseCommandHandlerFactory.h"

class CommandHandlerFactory: public Core::BaseCommandHandlerFactory
{
	static CommandHandlerFactory s_instance;
public:
	CommandHandlerFactory();
	virtual ~CommandHandlerFactory();

	virtual void Initialize() override;
	static CommandHandlerFactory& GetInstance()
	{
		return s_instance;
	}
};
