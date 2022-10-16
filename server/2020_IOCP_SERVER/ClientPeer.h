#pragma once
#include"framework.h"

class ClientPeer
{
	SOCKET m_socket;
	OVER_EX m_recvOver;
public:
	ClientPeer();
	virtual ~ClientPeer();

	void OnDisconnect();
	void Init(SOCKET ns);
};

