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
	for(auto& pair : m_requestHandlers)
		delete pair.second;

	m_requestHandlers.clear();
}

void BaseRequestHandlerFactory::HandleCommand(BasePacket* arg)
{
	if (m_requestHandlers.count(arg->type) == 0)
	{
		Logger::Error("��û �ڵ鷯�� �������� �ʽ��ϴ�. request = " + arg->type);
		return;
	}

	IRequestHandler* handler = m_requestHandlers[arg->type];
	handler->HandleRequest(arg);
}