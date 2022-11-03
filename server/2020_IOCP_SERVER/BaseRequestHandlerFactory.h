#pragma once
#include"RequestHandler.h"

class BaseRequestHandlerFactory
{
	std::unordered_map<unsigned char, RequestHandler*> m_requestHandlers;

protected:
	void AddHandler(unsigned char request, RequestHandler* handler);

public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	RequestHandler* CreateHandlerInstance(unsigned char type);
	virtual void Init() = 0;
};