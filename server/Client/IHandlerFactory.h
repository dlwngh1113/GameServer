#pragma once
#include "IFactory.h"

class BaseHandler;

class IHandlerFactory : public IFactory<Event, BaseHandler>
{
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<BaseHandler> Create(Event type) = 0;

	template<typename T>
	void AddHandlerCreator(Event key);
};

template<typename T>
inline void IHandlerFactory::AddHandlerCreator(Event key)
{
	AddCreator(key, std::make_unique<ProductCreator<BaseHandler, T>>());
}
