#pragma once

#include "Handler.h"

class HandlerFactory
{
	HandlerFactory();
	static HandlerFactory s_instance;
protected:
	std::unordered_map<Event, Handler*> m_handlers;
	void AddHandler(Event evt, Handler* handler);

public:
	virtual ~HandlerFactory();

	void Init();
	Handler* GetHandler(Event evt);

	static HandlerFactory& GetInstance() { return s_instance; }
};

