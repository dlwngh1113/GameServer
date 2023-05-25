#include "stdafx.h"
#include "IHandlerFactory.h"
#include "BaseRequestHandler.h"

void IHandlerFactory::AddHandler(short key, std::shared_ptr<BaseRequestHandler> value)
{
	m_handlers[key] = value;
}

IHandlerFactory::IHandlerFactory()
{
}

IHandlerFactory::~IHandlerFactory()
{
	m_handlers.clear();
}
