#pragma once
#include "Handler.h"

class LoginHandler : public Handler
{
public:
	LoginHandler();
	virtual ~LoginHandler();

	virtual void Handle() override;
	virtual Handler* Create() override;
};

