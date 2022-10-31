#pragma once
#include"BasePacket.h"

class IRequestHandler
{
protected:
public:
	virtual void HandleRequest(BasePacket* packet) = 0;
};
