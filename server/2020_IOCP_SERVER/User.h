#pragma once
#include"ClientPeer.h"

class User : protected ClientPeer
{
public:
	void ProcessPacket() override;
};