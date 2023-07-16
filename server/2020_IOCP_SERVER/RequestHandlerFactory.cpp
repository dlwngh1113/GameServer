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
	BaseRequestHandlerFactory::AddHandler<LoginRequestHandler>(static_cast<short>(ClientCommand::Login));
	BaseRequestHandlerFactory::AddHandler<MoveRequestHandler>(static_cast<short>(ClientCommand::Move));
	BaseRequestHandlerFactory::AddHandler<TeleportRequestHandler>(static_cast<short>(ClientCommand::Teleport));
	BaseRequestHandlerFactory::AddHandler<LogoutRequestHandler>(static_cast<short>(ClientCommand::Logout));
	BaseRequestHandlerFactory::AddHandler<PlaceEnterRequestHandler>(static_cast<short>(ClientCommand::PlaceEnter));
	Log("RequestHandlerFactory Init Finished");
}
