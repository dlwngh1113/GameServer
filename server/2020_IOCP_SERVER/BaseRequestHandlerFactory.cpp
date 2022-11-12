#include"stdafx.h"
#include "BaseRequestHandlerFactory.h"
#include"BaseRequestHandler.h"

BaseRequestHandlerFactory::BaseRequestHandlerFactory() : IFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
	for (auto& pair : m_handlers)
		delete pair.second;

	m_handlers.clear();
}

void BaseRequestHandlerFactory::AddHandler(unsigned char key, BaseRequestHandler* handler)
{
	m_handlers[key] = handler;
}

BaseRequestHandler* BaseRequestHandlerFactory::CreateHandlerInstance(unsigned char type)
{
	if (m_handlers.count(type) == 0)
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� �ڵ鷯�� �������� �ʽ��ϴ�.request = " + type };
	
	BaseRequestHandler* handler = m_handlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
