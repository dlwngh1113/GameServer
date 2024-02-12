#include "stdafx.h"
#include "CommandHandlerFactory.h"
#include "Logger.h"
#include "ChattingCommandHandler.h"

CommandHandlerFactory CommandHandlerFactory::s_instance;

CommandHandlerFactory::CommandHandlerFactory() : Core::BaseCommandHandlerFactory()
{
}

CommandHandlerFactory::~CommandHandlerFactory()
{
}

void CommandHandlerFactory::Initialize()
{
	Log("CommandHandlerFactory Init Started");
	AddHandlerCreator<ChattingCommandHandler>(static_cast<short>(ClientCommand::Chatting));
	Log("CommandHandlerFactory Init Finished");
}
