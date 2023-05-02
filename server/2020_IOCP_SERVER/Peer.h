#pragma once
#include "IPeer.h"
#include "Statics.h"

class IHandlerFactory;

class Peer : IPeer, public std::enable_shared_from_this<Peer>
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pRecvStartPos{ NULL };
	IHandlerFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
	void ReceiveLeftData(unsigned char* pNextRecvPos);
	void ProcessPacket(unsigned char size, unsigned char* data) override final;
public:
	explicit Peer(SOCKET socket);
	virtual ~Peer();

	int GetID() const { return static_cast<int>(m_socket); }

	void Initialize(IHandlerFactory* instance);
	void SendPacket(ClientCommon::BasePacket * packet);

	void ProcessIO(DWORD ioSize) override final;
	void SendPacket(unsigned char* data, unsigned short snSize) override final;
};