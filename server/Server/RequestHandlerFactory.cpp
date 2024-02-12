#include "stdafx.h"
#include "RequestHandlerFactory.h"
#include "Logger.h"
#include "ChattingCommandHandler.h"

RequestHandlerFactory RequestHandlerFactory::s_instance;

RequestHandlerFactory::RequestHandlerFactory() : Core::BaseRequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

void RequestHandlerFactory::Initialize()
{
	Log("RequestHandlerFactory Init Started");
	AddHandlerCreator<ChattingCommandHandler>(static_cast<short>(ClientCommand::Chatting));
	Log("RequestHandlerFactory Init Finished");
}
