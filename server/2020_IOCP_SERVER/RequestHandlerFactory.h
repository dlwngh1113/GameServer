#pragma once
#include"BaseRequestHandlerFactory.h"

class RequestHandlerFactory: protected BaseRequestHandlerFactory
{
	static RequestHandlerFactory* m_instance;
public:
	RequestHandlerFactory();
	virtual ~RequestHandlerFactory();

	RequestHandlerFactory* GetInstance() const;
};
