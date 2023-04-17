#include "stdafx.h"
#include "BaseRequestHandlerFactory.h"
#include "BaseRequestHandler.h"

BaseRequestHandlerFactory::BaseRequestHandlerFactory() : IHandlerFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
}

BaseRequestHandler* BaseRequestHandlerFactory::CreateInstance(short type)
{
	if (m_handlers.count(type) == 0)
		throw std::exception{ "해당 요청을 처리할 수 있는 핸들러가 존재하지 않습니다. request = " + type };
	
	BaseRequestHandler* handler = m_handlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "핸들러가 없습니다." };

	return handler;
}
