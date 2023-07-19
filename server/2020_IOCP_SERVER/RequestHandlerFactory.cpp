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
	BaseRequestHandlerFactory::AddHandlerCreator<LoginRequestHandler>(static_cast<short>(ClientCommand::Login));
	BaseRequestHandlerFactory::AddHandlerCreator<MoveRequestHandler>(static_cast<short>(ClientCommand::Move));
	BaseRequestHandlerFactory::AddHandlerCreator<TeleportRequestHandler>(static_cast<short>(ClientCommand::Teleport));
	BaseRequestHandlerFactory::AddHandlerCreator<LogoutRequestHandler>(static_cast<short>(ClientCommand::Logout));
	BaseRequestHandlerFactory::AddHandlerCreator<PlaceEnterRequestHandler>(static_cast<short>(ClientCommand::PlaceEnter));
	Log("RequestHandlerFactory Init Finished");
}
