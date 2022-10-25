#pragma once
#include"Logger.h"
#include"IPeer.h"

class ClientPeer : IPeer
{
	SOCKET m_socket;
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos;

protected:
	void StartRecv();
public:
	ClientPeer();
	virtual ~ClientPeer();

	void OnDisconnect();
	void Init(SOCKET ns);

	virtual void ProcessIO(DWORD ioSize);
	virtual void ProcessPacket(unsigned char size, unsigned char type);
};