#include "pch.h"
#include "HandlerFactory.h"
#include "Handlers.h"

void HandlerFactory::AddHandler(ServerEvent evt, Handler* handler)
{
	m_handlers.insert(std::make_pair<ServerEvent, Handler*>(evt, handler));
}

HandlerFactory::~HandlerFactory()
{
}

void HandlerFactory::Init()
{
	m_handlers.insert(std::make_pair<ServerEvent, Handler*>(ServerEvent::LoginOk, new LoginHandler));
}
