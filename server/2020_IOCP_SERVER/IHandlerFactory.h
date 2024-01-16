#pragma once
#include "IFactory.h"
#include "IHandlerCreator.h"

class BaseRequestHandler;

class IHandlerFactory : public IFactory<short, BaseRequestHandler>
{
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<BaseRequestHandler> Create(short type) = 0;
	
	template<typename T>
	void AddHandlerCreator(short key);
};

template<typename T>
inline void IHandlerFactory::AddHandlerCreator(short key)
{
	AddCreator(key, std::make_unique<ProductCreator<BaseRequestHandler, T>>());
}
