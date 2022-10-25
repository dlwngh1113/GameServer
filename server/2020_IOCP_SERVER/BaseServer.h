#pragma once
#include"ClientPeer.h"

class BaseServer
{
	HANDLE h_iocp;
	SOCKET m_listenSocket;
	OVER_EX m_acceptOver;

	std::mutex clientLock;
	std::unordered_map<SOCKET, ClientPeer*> m_clientPeers;
private:
	virtual void Init();
	void Listen();
	void AddNewClient(SOCKET socket);
	void DisconnectClient(SOCKET socket);

protected:
	void Process();
	virtual void Release();

	void OnAccept();

public:
	BaseServer();
	virtual ~BaseServer();

	virtual void Run();
};

