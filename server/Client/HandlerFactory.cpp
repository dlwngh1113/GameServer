#include "pch.h"
#include "HandlerFactory.h"
#include "EventHandlers.h"

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

void HandlerFactory::Initialize()
{
	AddHandlerCreator<ChattingEventHandler>(Event::Chatting);
	AddHandlerCreator<LoginCommandHandler>(Event::Login);
}