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
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Login) , std::make_shared<LoginRequestHandler>());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Move), std::make_shared<MoveRequestHandler>());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Teleport), std::make_shared<TeleportRequestHandler>());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Logout), std::make_shared<LogoutRequestHandler>());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::PlaceEnter), std::make_shared<PlaceEnterRequestHandler>());
	Log("RequestHandlerFactory Init Finished");
}
