#include"stdafx.h"
#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() : BaseRequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

void RequestHandlerFactory::Init()
{
	BaseRequestHandlerFactory::AddHandler(CS_LOGIN, new LoginRequestHandler());
}

RequestHandlerFactory* RequestHandlerFactory::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new RequestHandlerFactory();

	return m_instance;
}
