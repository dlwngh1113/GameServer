#pragma once
#include"ClientPeer.h"

class BaseServer
{
	HANDLE h_iocp;
	SOCKET m_listenSocket;
	OVER_EX m_acceptOver;

	std::list<ClientPeer*> m_clientPeers;
protected:
	virtual void Process() = 0;
	virtual void Release();

	void OnAccept();
public:
	BaseServer();
	virtual ~BaseServer();

	virtual void Run();
};

