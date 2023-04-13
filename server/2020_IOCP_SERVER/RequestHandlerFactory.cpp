#include"stdafx.h"
#include "RequestHandlerFactory.h"
#include"Logger.h"
#include"LoginRequestHandler.h"
#include"MoveRequestHandler.h"
#include"TeleportRequestHandler.h"
#include"LogoutRequestHandler.h"
#include"PlaceEnterRequestHandler.h"

RequestHandlerFactory* RequestHandlerFactory::m_instance = nullptr;

RequestHandlerFactory::RequestHandlerFactory() : BaseRequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	if (m_instance)
		delete m_instance;
}

void RequestHandlerFactory::Initialize()
{
	Log("RequestHandlerFactory Init Started");
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Login) , new LoginRequestHandler());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Move), new MoveRequestHandler());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Teleport), new TeleportRequestHandler());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::Logout), new LogoutRequestHandler());
	BaseRequestHandlerFactory::AddHandler(static_cast<short>(ClientCommand::PlaceEnter), new PlaceEnterRequestHandler());
	Log("RequestHandlerFactory Init Finished");
}

RequestHandlerFactory* RequestHandlerFactory::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new RequestHandlerFactory();

	return m_instance;
}
