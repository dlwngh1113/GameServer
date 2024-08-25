#include "stdafx.h"
#include "CommandHandlerFactory.h"
#include "Logger.h"
#include "ChattingCommandHandler.h"
#include "MoveCommandHandler.h"
#include "LoginCommandHandler.h"
#include "TeleportCommandHandler.h"

CommandHandlerFactory CommandHandlerFactory::s_instance;

CommandHandlerFactory::CommandHandlerFactory() : Core::BaseCommandHandlerFactory()
{
}

CommandHandlerFactory::~CommandHandlerFactory()
{
}

void CommandHandlerFactory::Initialize()
{
	Logger::instance().Log("CommandHandlerFactory Init Started");
	AddHandlerCreator<ChattingCommandHandler>(static_cast<short>(Command::Chatting));
	AddHandlerCreator<MoveCommandHandler>(static_cast<short>(Command::Move));
	AddHandlerCreator<LoginCommandHandler>(static_cast<short>(Command::Login));
	AddHandlerCreator<TeleportCommandHandler>(static_cast<short>(Command::Teleport));
	Logger::instance().Log("CommandHandlerFactory Init Finished");
}
