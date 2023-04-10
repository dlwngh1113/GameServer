#pragma once
#include"IHandlerFactory.h"

class BaseRequestHandlerFactory : public IHandlerFactory
{
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	BaseRequestHandler* CreateInstance(short type) override final;
	virtual void Init() = 0;
};
