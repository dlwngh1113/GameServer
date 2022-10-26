#pragma once
#include"ClientPeer.h"

class User : public ClientPeer
{
public:
	User();
	virtual ~User();

	void OnDisconnect() override;
	void ProcessPacket(BasePacket* packet) override;
};