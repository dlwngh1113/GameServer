#include"stdafx.h"
#include "BaseRequestHandlerFactory.h"

void BaseRequestHandlerFactory::AddHandler(unsigned char request, IRequestHandler* handler)
{
	m_requestHandlers[request] = handler;
}

BaseRequestHandlerFactory::BaseRequestHandlerFactory()
{
}

BaseRequestHandlerFactory::~BaseRequestHandlerFactory()
{
}

void BaseRequestHandlerFactory::HandleCommand(BasePacket* arg)
{
	if (m_requestHandlers.count(arg->type) == 0)
	{
		Logger::Error("요청 핸들러가 존재하지 않습니다. request = " + arg->type);
		return;
	}

	IRequestHandler* handler = m_requestHandlers[arg->type];
	handler->HandleRequest(arg);
}