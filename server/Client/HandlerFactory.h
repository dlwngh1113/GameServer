#pragma once
#include "IHandlerFactory.h"

class HandlerFactory : public IHandlerFactory
{
public:
	virtual std::shared_ptr<BaseHandler> Create(Event type) override;

//private:
//	static HandlerFactory s_instance;
//
//public:
//	static HandlerFactory instance() { return s_instance; }
};
