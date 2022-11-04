#pragma once
#include"BasePacket.h"
#include"Statics.h"
#include"IPeer.h"
#include"IFactory.h"

class ClientPeer : public IPeer
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos{ NULL };
	IFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
public:
	ClientPeer(SOCKET socket);
	virtual ~ClientPeer();

	int GetID() const { return static_cast<int>(m_socket); }

	void ProcessIO(DWORD ioSize);
	void Init(IFactory* instance);

	virtual void OnDisconnect();
	void ProcessPacket(unsigned char size, unsigned char* data) final;
	void SendPacket(unsigned char* data) final;
};