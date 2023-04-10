#pragma once
#include"IFactory.h"
class BaseRequestHandler;

class IHandlerFactory : public IFactory<short, BaseRequestHandler>
{
protected:
	std::unordered_map<short, BaseRequestHandler*> m_handlers;
	void AddHandler(short key, BaseRequestHandler* value);
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	BaseRequestHandler* CreateInstance(short key) = 0;
};