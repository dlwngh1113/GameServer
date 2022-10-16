#pragma once
#include"Logger.h"

class ClientPeer
{
	SOCKET m_socket;
	OVER_EX m_recvOver;
	std::mutex m_lock;
public:
	ClientPeer();
	virtual ~ClientPeer();

	void OnDisconnect();
	void Init(SOCKET ns);
};