#pragma once
#include "RequestHandler.h"

class ChattingCommandHandler : public RequestHandler
{
public:
	virtual void HandleRequest() override;
};
