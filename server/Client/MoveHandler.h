#pragma once
#include "Handler.h"

class MoveHandler : public Handler
{
public:
	MoveHandler();
	virtual ~MoveHandler();

	virtual void Handle() override;
	virtual Handler* Create() override;
};

