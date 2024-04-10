#pragma once
#include "IFactory.h"

class BaseHandler; 
	
class IHandlerFactory : public IFactory<short, BaseHandler>
{
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<BaseHandler> Create(short type) = 0;

	template<typename T>
	void AddHandlerCreator(short key);
};

template<typename T>
inline void IHandlerFactory::AddHandlerCreator(short key)
{
	AddCreator(key, std::make_unique<ProductCreator<BaseHandler, T>>());
}
