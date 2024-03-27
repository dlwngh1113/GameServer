#include "pch.h"
#include "HandlerFactory.h"
#include "Handlers.h"

HandlerFactory HandlerFactory::s_instance;

shared_ptr<BaseHandler> HandlerFactory::Create(Event evt)
{
	ICreator<BaseHandler>* creator = GetCreator(evt);

	if (creator == nullptr)
		throw std::exception{ "creator 가 존재하지 않습니다.\n" };

	return creator->Create();
}
