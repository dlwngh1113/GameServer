#pragma once
#include"Logger.h"
#include"BaseRequestHandlerFactory.h"
#include"LoginRequestHandler.h"
#include"MoveRequestHandler.h"
#include"TeleportRequestHandler.h"
#include"LogoutRequestHandler.h"

class RequestHandlerFactory: public BaseRequestHandlerFactory
{
	static RequestHandlerFactory* m_instance;
public:
	RequestHandlerFactory();
	virtual ~RequestHandlerFactory();

	void Init() override;
	static RequestHandlerFactory* GetInstance();
};
