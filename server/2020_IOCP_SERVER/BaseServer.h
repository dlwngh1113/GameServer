#pragma once
#include"ClientPeer.h"

class BaseServer
{
	std::list<ClientPeer*> m_clientPeers;
public:
	BaseServer();
	virtual ~BaseServer();
};

