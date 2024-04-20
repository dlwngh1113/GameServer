#include "pch.h"
#include "HandlerFactory.h"

HandlerFactory::HandlerFactory()
{
}

HandlerFactory::~HandlerFactory()
{
}

std::shared_ptr<BaseHandler> HandlerFactory::Create(Event type)
{
	ICreator<BaseHandler>* creator = GetCreator(type);
	if (!creator)
		throw std::exception{ "해당 요청을 처리할 수 있는 Creator가 존재하지 않습니다. request = " + (short)type };

	std::shared_ptr<BaseHandler> handler = creator->Create();

	if (handler == nullptr)
		throw std::exception{ "핸들러가 없습니다." };

	return handler;
}
