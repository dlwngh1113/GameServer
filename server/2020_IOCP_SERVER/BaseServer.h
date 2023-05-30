#pragma once
#include "Peer.h"

class BaseServer
{
	HANDLE h_iocp;
	SOCKET m_listenSocket;
	OVER_EX m_acceptOver;

	std::mutex clientLock;
	std::unordered_map<SOCKET, std::shared_ptr<Peer>> m_peers;
	ThreadPool m_threadPool;
private:
	void Initialize();
	void Listen();
	void BeginAcceptPeer();

	void AddNewClient(SOCKET socket);
	void DisconnectClient(SOCKET socket);

protected:
	void Process();
	void Release();

	virtual void OnAccept(const SOCKET socket, Peer* peer) = 0;
	virtual void OnDisconnected(const SOCKET socket) = 0;

public:
	BaseServer();
	virtual ~BaseServer();
	void AddWork(std::function<void()> work) { m_threadPool.EnqueWork(std::move(work)); }

	virtual void Run();
};