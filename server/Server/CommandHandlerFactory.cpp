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
	//Logger::instance().Log("CommandHandlerFactory Init Started");
	AddHandlerCreator<ChattingCommandHandler>(static_cast<short>(ClientCommand::Chatting));
	//Logger::instance().Log("CommandHandlerFactory Init Finished");
}
