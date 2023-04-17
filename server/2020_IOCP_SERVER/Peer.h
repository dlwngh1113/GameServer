#pragma once
#include "IPeer.h"
#include "Statics.h"

class IHandlerFactory;

class Peer : IPeer
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos{ NULL };
	IHandlerFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
public:
	explicit Peer(SOCKET socket);
	virtual ~Peer();

	int GetID() const { return static_cast<int>(m_socket); }

	void ProcessIO(DWORD ioSize);
	void Initialize(IHandlerFactory* instance);

	void ProcessPacket(unsigned char size, unsigned char* data) final;
	void SendPacket(unsigned char* data) final;
	void SendPacket(ClientCommon::BasePacket * packet);
};