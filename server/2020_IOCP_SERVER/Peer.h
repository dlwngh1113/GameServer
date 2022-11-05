#pragma once
#include"IPeer.h"
#include"BasePacket.h"
#include"Statics.h"
#include"IFactory.h"

class Peer : IPeer
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos{ NULL };
	IFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
public:
	Peer(SOCKET socket);
	virtual ~Peer();

	int GetID() const { return static_cast<int>(m_socket); }

	void ProcessIO(DWORD ioSize);
	void Init(IFactory* instance);

	virtual void OnDisconnect();
	void ProcessPacket(unsigned char size, unsigned char* data) final;
	void SendPacket(unsigned char* data) final;
};