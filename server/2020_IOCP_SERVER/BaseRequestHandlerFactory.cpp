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
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� �ڵ鷯�� �������� �ʽ��ϴ�.request = " + type };
	
	RequestHandler* handler = m_requestHandlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
