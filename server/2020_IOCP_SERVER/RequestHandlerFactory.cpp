#include "stdafx.h"
#include "RequestHandlerFactory.h"
#include "Logger.h"
#include "LoginRequestHandler.h"
#include "MoveRequestHandler.h"
#include "TeleportRequestHandler.h"
#include "LogoutRequestHandler.h"
#include "PlaceEnterRequestHandler.h"

RequestHandlerFactory RequestHandlerFactory::s_instance;

RequestHandlerFactory::RequestHandlerFactory() : BaseRequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

void RequestHandlerFactory::Initialize()
{
	Log("RequestHandlerFactory Init Started");
	AddHandlerCreator<LoginRequestHandler>(static_cast<short>(ClientCommand::Login));
	AddHandlerCreator<MoveRequestHandler>(static_cast<short>(ClientCommand::Move));
	AddHandlerCreator<TeleportRequestHandler>(static_cast<short>(ClientCommand::Teleport));
	AddHandlerCreator<LogoutRequestHandler>(static_cast<short>(ClientCommand::Logout));
	AddHandlerCreator<PlaceEnterRequestHandler>(static_cast<short>(ClientCommand::PlaceEnter));
	Log("RequestHandlerFactory Init Finished");
}
