#pragma once
#include"BasePacket.h"

class IRequestHandler
{
public:
	virtual void HandleRequest(BasePacket* packet) = 0;
};
