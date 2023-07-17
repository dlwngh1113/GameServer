#pragma once
#include "IHandlerFactory.h"

class BaseRequestHandler;

class BaseRequestHandlerFactory : public IHandlerFactory
{
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	std::shared_ptr<IRequestHandler> CreateInstance(short type) override final;
	virtual void Initialize() = 0;
};
