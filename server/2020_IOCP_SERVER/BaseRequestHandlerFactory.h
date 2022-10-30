#pragma once
#include"IRequestHandler.h"
#include"Logger.h"

class BaseRequestHandlerFactory
{
	std::unordered_map<unsigned char, IRequestHandler*> m_requestHandlers;

protected:
	void AddHandler(unsigned char request, IRequestHandler* handler);

public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	virtual void HandleCommand(BasePacket* arg);
	virtual void Init() = 0;
};