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
			throw exception{ "해당 요청을 처리할 수 있는 Creator가 존재하지 않습니다. request = " + type };

		shared_ptr<BaseRequestHandler> handler = creator->Create();

		if (handler == nullptr)
			throw exception{ "핸들러가 없습니다." };

		return handler;
	}
}