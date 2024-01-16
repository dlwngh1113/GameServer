#include "stdafx.h"
#include "BaseRequestHandlerFactory.h"
#include "BaseRequestHandler.h"

BaseRequestHandlerFactory::BaseRequestHandlerFactory() : IHandlerFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
}

std::shared_ptr<BaseRequestHandler> BaseRequestHandlerFactory::Create(short type)
{
	ICreator<BaseRequestHandler>* creator = GetCreator(type);
	if (!creator)
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� Creator�� �������� �ʽ��ϴ�. request = " + type };

	std::shared_ptr<BaseRequestHandler> handler = creator->Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
