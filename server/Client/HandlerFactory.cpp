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
		throw std::exception{ "�ش� ��û�� ó���� �� �ִ� Creator�� �������� �ʽ��ϴ�. request = " + (short)type };

	std::shared_ptr<BaseHandler> handler = creator->Create();

	if (handler == nullptr)
		throw std::exception{ "�ڵ鷯�� �����ϴ�." };

	return handler;
}
