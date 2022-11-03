#include"stdafx.h"
#include "BaseRequestHandlerFactory.h"
#include"RequestHandler.h"

BaseRequestHandlerFactory::BaseRequestHandlerFactory() : IFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
	for (auto& pair : m_handlers)
		delete pair.second;

	m_handlers.clear();
}

void BaseRequestHandlerFactory::AddHandler(unsigned char key, RequestHandler* handler)
{
	m_handlers[key] = handler;
}

RequestHandler* BaseRequestHandlerFactory::CreateHandlerInstance(unsigned char type)
{
	if (m_handlers.count(type) == 0)
		throw std::exception{ "해당 요청을 처리할 수 있는 핸들러가 존재하지 않습니다.request = " + type };
	
	RequestHandler* handler = m_handlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "핸들러가 없습니다." };

	return handler;
}
