#pragma once
#include "IHandlerFactory.h"

class BaseRequestHandlerFactory : public IHandlerFactory
{
public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	virtual std::shared_ptr<BaseRequestHandler> Create(short type) override;
	virtual void Initialize() = 0;
};
