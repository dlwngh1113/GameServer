#pragma once
#include"IFactory.h"
class BaseRequestHandler;

class IHandlerFactory : public IFactory<unsigned char, BaseRequestHandler>
{
protected:
	std::unordered_map<unsigned char, BaseRequestHandler*> m_handlers;
	void AddHandler(unsigned char key, BaseRequestHandler* value);
public:
	IHandlerFactory();
	virtual ~IHandlerFactory();

	BaseRequestHandler* CreateInstance(unsigned char key) = 0;
};