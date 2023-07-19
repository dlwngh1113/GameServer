#pragma once
#include "IFactory.h"

template<typename TBaseHandlerType>
class IHandlerFactory : public IFactory<short, TBaseHandlerType>
{
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<TBaseHandlerType> Create(short key) = 0;
};

template<typename TBaseHandlerType>
inline IHandlerFactory<TBaseHandlerType>::IHandlerFactory()
{
}

template<typename TBaseHandlerType>
inline IHandlerFactory<TBaseHandlerType>::~IHandlerFactory()
{
}
