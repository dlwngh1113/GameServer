#pragma once
#include"Peer.h"

class BaseServer
{
	HANDLE h_iocp;
	SOCKET m_listenSocket;
	OVER_EX m_acceptOver;

	std::mutex clientLock;
	std::unordered_map<SOCKET, Peer*> m_peers;
private:
	void Listen();
	void AddNewClient(SOCKET socket);
	void DisconnectClient(SOCKET socket);

protected:
	void Process();
	virtual void Release();

	void BeginAcceptPeer();
	virtual void OnAccept(const SOCKET socket, Peer*& peer) = 0;
	virtual void OnDisconnected(SOCKET socket) = 0;

public:
	BaseServer();
	virtual ~BaseServer();

	virtual void Init();
	virtual void Run();
};