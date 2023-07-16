#include "stdafx.h"
#include "BaseRequestHandlerFactory.h"
#include "BaseRequestHandler.h"

BaseRequestHandlerFactory::BaseRequestHandlerFactory() : IHandlerFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
}

std::shared_ptr<BaseRequestHandler> BaseRequestHandlerFactory::CreateInstance(short type)
{
	if (m_creators.count(type) == 0)
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� �ڵ鷯�� �������� �ʽ��ϴ�. request = " + type };
	
	std::shared_ptr<BaseRequestHandler> handler = m_creators[type].Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
