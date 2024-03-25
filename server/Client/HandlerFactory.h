#pragma once

#include "IFactory.h"
#include "Handler.h"

class HandlerFactory : public IFactory<Event, Handler>
{
private:
	HandlerFactory();
	static HandlerFactory s_instance;

protected:
	template <typename T>
	void AddHandler(Event evt, T handler);

public:
	virtual ~HandlerFactory();

	void Init();
	Handler* GetHandler(Event evt);

	static HandlerFactory& GetInstance() { return s_instance; }
};

