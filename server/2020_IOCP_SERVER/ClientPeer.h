#pragma once
#include"Logger.h"
#include"IPeer.h"

class ClientPeer : IPeer
{
	SOCKET m_socket;
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos;

	void StartRecv();
public:
	ClientPeer();
	virtual ~ClientPeer();

	void ProcessIO(DWORD ioSize);
	void Init(SOCKET ns);

	virtual void OnDisconnect();
	virtual void ProcessPacket(BasePacket* packet);
};