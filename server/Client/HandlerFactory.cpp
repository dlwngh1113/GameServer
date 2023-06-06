#include "pch.h"
#include "HandlerFactory.h"
#include "Handlers.h"

void HandlerFactory::AddHandler(ServerEvent evt, Handler* handler)
{
	m_handlers.insert(std::pair<ServerEvent, Handler*>(evt, handler));
}

HandlerFactory::~HandlerFactory()
{
}

void HandlerFactory::Init()
{
	m_handlers.insert(std::make_pair<ServerEvent, Handler*>(ServerEvent::LoginOk, new LoginHandler));
}

Handler* HandlerFactory::GetHandler(ServerEvent evt)
{
	Handler* handler = nullptr;

	if (m_handlers.count(evt))
	{
		std::cout << (int)evt << "handler �� �������� �ʽ��ϴ�.\n";
		return nullptr;
	}

	handler = m_handlers[evt]->Create();
	if (handler == nullptr)
	{
		std::cout << (int)evt << "Handler Create �Լ��� �������� �ʽ��ϴ�.\n";
		return nullptr;
	}

	return handler;
}
