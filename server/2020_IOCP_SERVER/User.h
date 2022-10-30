#pragma once
#include"ClientPeer.h"
#include"RequestHandlerFactory.h"

class User : public ClientPeer
{
public:
	User(BaseRequestHandlerFactory* instance);
	virtual ~User();

	void OnDisconnect() override;
	void ProcessPacket(BasePacket* packet) override;
};