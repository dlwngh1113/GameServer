#pragma once
#include"ClientPeer.h"

class User : protected ClientPeer
{
public:
	void ProcessPacket(unsigned char size, unsigned char type) override;
};