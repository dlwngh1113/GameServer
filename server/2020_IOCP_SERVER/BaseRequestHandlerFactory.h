#pragma once
#include"IHandlerFactory.h"

class BaseRequestHandlerFactory : public IHandlerFactory
{
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	BaseRequestHandler* CreateInstance(unsigned char type) override final;
	virtual void Init() = 0;
};
