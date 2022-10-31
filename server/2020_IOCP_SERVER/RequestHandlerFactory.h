#pragma once
#include"BaseRequestHandlerFactory.h"
#include"LoginRequestHandler.h"

class RequestHandlerFactory: public BaseRequestHandlerFactory
{
	static RequestHandlerFactory* m_instance;
public:
	RequestHandlerFactory();
	virtual ~RequestHandlerFactory();

	void Init() override;
	static RequestHandlerFactory* GetInstance();
};
