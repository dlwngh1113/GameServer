#pragma once
#include "BaseRequestHandlerFactory.h"

class RequestHandlerFactory: public BaseRequestHandlerFactory
{
	static RequestHandlerFactory s_instance;
public:
	RequestHandlerFactory();
	virtual ~RequestHandlerFactory();

	void Initialize() override;
	static RequestHandlerFactory& GetInstance()
	{
		return s_instance;
	}
};
