#pragma once
#include"ClientPeer.h"

class BaseServer
{
	std::list<ClientPeer*> m_clientPeers;
protected:
	virtual void Run() = 0;
	virtual void Release() = 0;
public:
	BaseServer();
	virtual ~BaseServer();
};

