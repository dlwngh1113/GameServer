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
		throw std::exception{ "handler �� �������� �ʽ��ϴ�.\n" };

	handler = m_handlers[evt]->Create();
	if (handler == nullptr)
		throw std::exception{ "Handler Create �Լ��� �������� �ʽ��ϴ�.\n" };

	return handler;
}
