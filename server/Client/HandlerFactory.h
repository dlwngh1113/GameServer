#pragma once

#include "IHandlerFactory.h"
#include "BaseHandler.h"

class HandlerFactory : public IHandlerFactory
{
public:
	virtual ~HandlerFactory() {}

	virtual std::shared_ptr<BaseHandler> Create(Event key) override;

private:
	static HandlerFactory s_instance;

public:
	static HandlerFactory instance() { return s_instance; }
};
