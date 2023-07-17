#pragma once
#include "IFactory.h"
#include "HandlerCreator.h"

class BaseRequestHandler;

class IHandlerFactory : public IFactory<short, std::unique_ptr<IHandlerCreator>>
{
protected:
	template<typename T>
	void AddHandler(short key);
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	virtual std::shared_ptr<IRequestHandler> CreateInstance(short key) = 0;
};

template<typename T>
inline void IHandlerFactory::AddHandler(short key)
{
	m_creators.insert(std::make_pair<short, std::unique_ptr<IHandlerCreator>>(std::move(key), std::make_unique<HandlerCreator<T>>()));
}
