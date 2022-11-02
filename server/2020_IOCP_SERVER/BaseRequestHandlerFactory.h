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

	IRequestHandler* CreateHandlerInstance(unsigned char type);
	virtual void Init() = 0;
};