#pragma once

#include "IFactory.h"
#include "BaseHandler.h"

class HandlerFactory : public IFactory<Event, BaseHandler>
{
public:
	HandlerFactory();
	virtual ~HandlerFactory();

	virtual shared_ptr<BaseHandler> Create(Event key);

	template<typename T>
	void AddHandlerCreator(Event key);

private:
	static HandlerFactory s_instance;

public:
	static HandlerFactory instance() { return s_instance; }
};

template<typename T>
inline void HandlerFactory::AddHandlerCreator(Event key)
{
	AddCreator(key, make_unique<ProductCreator<BaseHandler, T>>());
}
