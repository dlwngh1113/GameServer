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
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� �ڵ鷯�� �������� �ʽ��ϴ�. request = " + type };
	
	BaseRequestHandler* handler = m_handlers[type]->Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
