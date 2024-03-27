#include "pch.h"
#include "HandlerFactory.h"
#include "Handlers.h"

HandlerFactory HandlerFactory::s_instance;

shared_ptr<BaseHandler> HandlerFactory::Create(Event evt)
{
	ICreator<BaseHandler>* creator = GetCreator(evt);

	if (creator == nullptr)
		throw std::exception{ "creator �� �������� �ʽ��ϴ�.\n" };

	return creator->Create();
}
