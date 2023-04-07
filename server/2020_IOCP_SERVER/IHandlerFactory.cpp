#include "stdafx.h"
#include "IHandlerFactory.h"
#include"BaseRequestHandler.h"

void IHandlerFactory::AddHandler(short key, BaseRequestHandler* value)
{
	m_handlers[key] = value;
}

IHandlerFactory::IHandlerFactory()
{
}

IHandlerFactory::~IHandlerFactory()
{
	for (auto& pair : m_handlers)
		delete pair.second;

	m_handlers.clear();
}
