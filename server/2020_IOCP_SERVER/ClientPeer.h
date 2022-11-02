#pragma once
#include"ObjectPool.h"
#include"BaseRequestHandlerFactory.h"
#include"IPeer.h"

ObjectPool<OVER_EX> g_OverExPool{ MAX_USER / 2 };

class ClientPeer : IPeer
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos{ NULL };
	BaseRequestHandlerFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
public:
	ClientPeer(SOCKET socket);
	virtual ~ClientPeer();

	int GetID()const { return static_cast<int>(m_socket); }

	void ProcessIO(DWORD ioSize);
	void Init(BaseRequestHandlerFactory* instance);

	virtual void OnDisconnect();
	void ProcessPacket(unsigned char size, unsigned char* data) final;
	void SendPacket(unsigned char* data) final;
};