#pragma once
#include"IRequestHandler.h"
#include"Logger.h"

class IRequestHandlerFactory
{
	std::unordered_map<unsigned char, IRequestHandler*> m_requestHandlers;
protected:
	void AddHandler(unsigned char request, IRequestHandler* handler);
public:
	virtual void HandleCommand(BasePacket* arg);
};