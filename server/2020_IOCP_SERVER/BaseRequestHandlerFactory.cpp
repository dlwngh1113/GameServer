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
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� �ڵ鷯�� �������� �ʽ��ϴ�.request = " + type };
	
	RequestHandler* handler = m_handlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
