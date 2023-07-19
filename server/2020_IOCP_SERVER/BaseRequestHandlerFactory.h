#pragma once
#include "IHandlerFactory.h"

class BaseRequestHandlerFactory : public IHandlerFactory
{
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	std::shared_ptr<BaseRequestHandler> Create(short type) override final;
	virtual void Initialize() = 0;
};
