#pragma once
#include "IFactory.h"
#include "HandlerCreator.h"

class BaseRequestHandler;

class IHandlerFactory : public IFactory<short, BaseRequestHandler>
{
protected:
	template<typename THandlerType>
	void AddHandlerCreator(short key);
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<BaseRequestHandler> Create(short key) = 0;
};

template<typename THandlerType>
inline void IHandlerFactory::AddHandlerCreator(short key)
{
	m_creators.insert(std::make_pair(key, std::make_unique<HandlerCreator<THandlerType>>()));
}
