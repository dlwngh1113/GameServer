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
		throw std::exception{ "handler 가 존재하지 않습니다.\n" };

	handler = m_creators[evt]->Create();
	if (handler == nullptr)
		throw std::exception{ "Handler Create 함수가 존재하지 않습니다.\n" };

	return handler;
}
