#include "pch.h"
#include "HandlerFactory.h"
#include "Handlers.h"

HandlerFactory HandlerFactory::s_instance;

HandlerFactory::HandlerFactory()
{
}

HandlerFactory::~HandlerFactory()
{
	for (auto& pair : m_handlers)
		delete pair.second;

	m_handlers.clear();
}

void HandlerFactory::AddHandler(ServerEvent evt, Handler* handler)
{
	m_handlers.insert(std::pair<ServerEvent, Handler*>(evt, handler));
}

void HandlerFactory::Init()
{
	m_handlers.insert(std::make_pair<ServerEvent, Handler*>(ServerEvent::LoginOk, new LoginHandler));
}

Handler* HandlerFactory::GetHandler(ServerEvent evt)
{
	Handler* handler = nullptr;

	if (m_handlers.count(evt))
		throw std::exception{ "handler 가 존재하지 않습니다.\n" };

	handler = m_handlers[evt]->Create();
	if (handler == nullptr)
		throw std::exception{ "Handler Create 함수가 존재하지 않습니다.\n" };

	return handler;
}
