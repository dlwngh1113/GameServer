#pragma once
#include "IHandlerFactory.h"
#include "HandlerCreator.h"

class BaseRequestHandler;

class BaseRequestHandlerFactory : public IHandlerFactory<BaseRequestHandler>
{
protected:
	template<typename THandlerType>
	void AddHandler(short key);

public:
	BaseRequestHandlerFactory();
	virtual ~BaseRequestHandlerFactory();

	std::shared_ptr<BaseRequestHandler> Create(short type) override final;
	virtual void Initialize() = 0;
};

template<typename THandlerType>
inline void BaseRequestHandlerFactory::AddHandler(short key)
{
	m_creators.insert(std::make_pair(key, HandlerCreator<THandlerType>()));
}
