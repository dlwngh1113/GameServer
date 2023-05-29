#pragma once
#include "IFactory.h"

class BaseRequestHandler;

class IHandlerFactory : public IFactory<short, BaseRequestHandler>
{
protected:
	std::unordered_map<short, std::shared_ptr<BaseRequestHandler>> m_handlers;
	void AddHandler(short key, std::shared_ptr<BaseRequestHandler> value);
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	std::shared_ptr<BaseRequestHandler> CreateInstance(short key) = 0;
};