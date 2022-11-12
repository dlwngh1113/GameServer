#pragma once
#include"IFactory.h"
#include"BaseRequestHandler.h"

class BaseRequestHandlerFactory : public IFactory
{
	std::unordered_map<unsigned char, BaseRequestHandler*> m_handlers;
protected:
	void AddHandler(unsigned char key, BaseRequestHandler* handler);
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	BaseRequestHandler* CreateHandlerInstance(unsigned char type);
	virtual void Init() = 0;
};
