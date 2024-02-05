#include "stdafx.h"
#include "RequestHandlerFactory.h"
#include "Logger.h"

RequestHandlerFactory RequestHandlerFactory::s_instance;

RequestHandlerFactory::RequestHandlerFactory() : Core::BaseRequestHandlerFactory()
{
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

void RequestHandlerFactory::Initialize()
{
	Log("RequestHandlerFactory Init Started");
	Log("RequestHandlerFactory Init Finished");
}
