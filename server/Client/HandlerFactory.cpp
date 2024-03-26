#include "pch.h"
#include "HandlerFactory.h"
#include "Handlers.h"

HandlerFactory HandlerFactory::s_instance;

HandlerFactory::HandlerFactory()
{
}

HandlerFactory::~HandlerFactory()
{
}

shared_ptr<BaseHandler> HandlerFactory::Create(Event evt)
{
	shared_ptr<BaseHandler> handler = nullptr;

	if (m_creators.count(evt) == 0)
		throw std::exception{ "handler �� �������� �ʽ��ϴ�.\n" };

	handler = m_creators[evt]->Create();
	if (handler == nullptr)
		throw std::exception{ "Handler Create �Լ��� �������� �ʽ��ϴ�.\n" };

	return handler;
}
