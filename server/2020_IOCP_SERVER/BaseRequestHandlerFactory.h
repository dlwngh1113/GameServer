#pragma once
#include"IFactory.h"
#include"RequestHandler.h"

class BaseRequestHandlerFactory : public IFactory
{
	std::unordered_map<unsigned char, RequestHandler*> m_handlers;
protected:
	void AddHandler(unsigned char key, RequestHandler* handler);
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	RequestHandler* CreateHandlerInstance(unsigned char type);
	virtual void Init() = 0;
};
