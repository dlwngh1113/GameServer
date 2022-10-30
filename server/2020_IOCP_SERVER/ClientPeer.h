#pragma once
#include"BaseRequestHandlerFactory.h"
#include"IPeer.h"

class ClientPeer : IPeer
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos{ NULL };
	BaseRequestHandlerFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
public:
	ClientPeer();
	virtual ~ClientPeer();

	void ProcessIO(DWORD ioSize);
	void Init(SOCKET ns);

	virtual void OnDisconnect();
	void ProcessPacket(unsigned char size, unsigned char* data) final;
	virtual void ProcessPacket(BasePacket* packet);
};