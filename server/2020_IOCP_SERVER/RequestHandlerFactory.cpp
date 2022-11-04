#include"stdafx.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory* RequestHandlerFactory::m_instance = nullptr;

RequestHandlerFactory::RequestHandlerFactory() : BaseRequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

void RequestHandlerFactory::Init()
{
	Logger::Info("RequestHandlerFactory Init Started");
	BaseRequestHandlerFactory::AddHandler(CS_LOGIN, new LoginRequestHandler());
	BaseRequestHandlerFactory::AddHandler(CS_MOVE, new MoveRequestHandler());
	Logger::Info("RequestHandlerFactory Init Finished");
}

RequestHandlerFactory* RequestHandlerFactory::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new RequestHandlerFactory();

	return m_instance;
}
