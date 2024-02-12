#include "stdafx.h"
#include "BaseRequestHandlerFactory.h"
#include "BaseRequestHandler.h"

namespace Core
{
	BaseRequestHandlerFactory::BaseRequestHandlerFactory() : IHandlerFactory()
	{
	}

	BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
	{
	}

	shared_ptr<BaseRequestHandler> BaseRequestHandlerFactory::Create(short type)
	{
		ICreator<BaseRequestHandler>* creator = GetCreator(type);
		if (!creator)
			throw exception{ "�ش� ��û�� ó���� �� �ִ� Creator�� �������� �ʽ��ϴ�. request = " + type };

		shared_ptr<BaseRequestHandler> handler = creator->Create();

		if (handler == nullptr)
			throw exception{ "�ڵ鷯�� �����ϴ�." };

		return handler;
	}
}