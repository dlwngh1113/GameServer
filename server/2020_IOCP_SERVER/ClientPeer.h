#pragma once
#include"framework.h"

class ClientPeer
{
	SOCKET m_socket;
public:
	ClientPeer();
	virtual ~ClientPeer();

	void Init(SOCKET ns);
};

