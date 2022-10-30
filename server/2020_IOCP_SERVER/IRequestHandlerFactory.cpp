#include "IRequestHandlerFactory.h"

void IRequestHandlerFactory::AddHandler(unsigned char request, IRequestHandler* handler)
{
	m_requestHandlers[request] = handler;
}

void IRequestHandlerFactory::HandleCommand(BasePacket* arg)
{
	if (m_requestHandlers.count(arg->type) == 0)
	{
		Logger::Error("요청 핸들러가 존재하지 않습니다. request = " + arg->type);
		return;
	}

	IRequestHandler* handler = m_requestHandlers[arg->type];
	handler->HandleRequest();
}
