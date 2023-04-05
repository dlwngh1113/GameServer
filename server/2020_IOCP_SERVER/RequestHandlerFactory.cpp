#include"stdafx.h"
#include "RequestHandlerFactory.h"
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

void RequestHandlerFactory::Init()
{
	Log("RequestHandlerFactory Init Started");
	BaseRequestHandlerFactory::AddHandler(CS_LOGIN, new LoginRequestHandler());
	BaseRequestHandlerFactory::AddHandler(CS_MOVE, new MoveRequestHandler());
	BaseRequestHandlerFactory::AddHandler(CS_TELEPORT, new TeleportRequestHandler());
	BaseRequestHandlerFactory::AddHandler(CS_LOGOUT, new LogoutRequestHandler());
	BaseRequestHandlerFactory::AddHandler(CS_ENTERPLACE, new PlaceEnterRequestHandler());
	Log("RequestHandlerFactory Init Finished");
}

RequestHandlerFactory* RequestHandlerFactory::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new RequestHandlerFactory();

	return m_instance;
}
