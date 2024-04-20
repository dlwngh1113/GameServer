#pragma once
#include "IHandlerFactory.h"

class HandlerFactory : public IHandlerFactory
{
public:
	HandlerFactory();
	virtual ~HandlerFactory();

	virtual std::shared_ptr<BaseHandler> Create(Event type) override;
};
