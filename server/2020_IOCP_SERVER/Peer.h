#pragma once
#include "IPeer.h"
#include "Global.h"

class BaseRequestHandlerFactory;

class Peer : public IPeer
{
	SOCKET m_socket{ NULL };
	OVER_EX m_recvOver;
	std::mutex m_lock;

	unsigned char* m_pReceiveStartPtr{ NULL };
	BaseRequestHandlerFactory* m_requestHandlerFactory = nullptr;

	void StartRecv();
	void ReceiveLeftData(unsigned char* pNextRecvPos);
	void ProcessPacket(unsigned char* data, unsigned short snSize) override final;
public:
	explicit Peer(SOCKET socket);
	virtual ~Peer();

	int GetID() const { return static_cast<int>(m_socket); }

	void Initialize(BaseRequestHandlerFactory* instance);
	void SendPacket(ClientCommon::BasePacket * packet);

	void ProcessIO(DWORD ioSize) override final;
	void SendPacket(unsigned char* data, unsigned short snSize) override final;
};