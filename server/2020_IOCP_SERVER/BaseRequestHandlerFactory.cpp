#include"stdafx.h"
#include "BaseRequestHandlerFactory.h"

void BaseRequestHandlerFactory::AddHandler(unsigned char request, IRequestHandler* handler)
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

IRequestHandler* BaseRequestHandlerFactory::CreateHandlerInstance(unsigned char type)
{
	IRequestHandler* handler = nullptr;

	try
	{
		if (m_requestHandlers.count(type) == 0)
			throw std::exception{ "해당 요청을 처리할 수 있는 핸들러가 존재하지 않습니다.request = " + type };

		handler = m_requestHandlers[type];
	}
	catch (std::exception& ex)
	{
		Logger::Error(ex.what());
	}

	return handler;
}