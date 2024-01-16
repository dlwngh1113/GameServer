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
		throw std::exception{ "해당 요청을 처리할 수 있는 Creator가 존재하지 않습니다. request = " + type };

	std::shared_ptr<BaseRequestHandler> handler = creator->Create();

	if (handler == nullptr)
		throw std::exception{ "핸들러가 없습니다." };

	return handler;
}
