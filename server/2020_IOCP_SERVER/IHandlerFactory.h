#pragma once
#include "IFactory.h"
#include "HandlerCreator.h"

class BaseRequestHandler;

class IHandlerFactory : public IFactory<short, HandlerCreator<BaseRequestHandler>>
{
protected:
	template<typename T>
	void AddHandler(short key);
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<BaseRequestHandler> CreateInstance(short key) = 0;
};

template<typename T>
inline void IHandlerFactory::AddHandler(short key)
{
	m_creators.insert(key, HandlerCreator<T>{});
}
