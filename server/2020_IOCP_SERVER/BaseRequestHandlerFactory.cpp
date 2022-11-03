#include"stdafx.h"
#include "BaseRequestHandlerFactory.h"

void BaseRequestHandlerFactory::AddHandler(unsigned char request, RequestHandler* handler)
{
	m_requestHandlers[request] = handler;
}

BaseRequestHandlerFactory::BaseRequestHandlerFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
	for(auto& pair : m_requestHandlers)
		delete pair.second;

	m_requestHandlers.clear();
}

RequestHandler* BaseRequestHandlerFactory::CreateHandlerInstance(unsigned char type)
{
	if (m_requestHandlers.count(type) == 0)
		throw std::exception{ "해당 요청을 처리할 수 있는 핸들러가 존재하지 않습니다.request = " + type };
	
	RequestHandler* handler = m_requestHandlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "핸들러가 없습니다." };

	return handler;
}
