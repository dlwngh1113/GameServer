#pragma once

#include "Handler.h"

class HandlerFactory
{
	HandlerFactory();
	static HandlerFactory s_instance;
protected:
	std::unordered_map<ServerEvent, Handler*> m_handlers;
	void AddHandler(ServerEvent evt, Handler* handler);

public:
	virtual ~HandlerFactory();

	void Init();
	Handler* GetHandler(ServerEvent evt);

	static HandlerFactory& GetInstance() { return s_instance; }
};

