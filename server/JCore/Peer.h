#pragma once
#include <WinSock2.h>
#include <mutex>
#include <iostream>
#include "IPeer.h"
#include "OverlappedExtension.h"

class BaseRequestHandlerFactory;

namespace JCore
{
	class Peer : public IPeer
	{
		SOCKET m_socket{ NULL };
		OverlappedExtension m_recvOver;
		std::mutex m_lock;

		unsigned char* m_pReceiveStartPtr{ NULL };

		void StartRecv();
		void ReceiveLeftData(unsigned char* pNextRecvPos);
		virtual void OnProcessPacket(unsigned char* data, unsigned short snSize) = 0;
	public:
		explicit Peer(SOCKET socket);
		virtual ~Peer();

		int GetID() const { return static_cast<int>(m_socket); }

		void ProcessIO(DWORD ioSize) override final;
		void SendPacket(unsigned char* data, unsigned short snSize) override final;
	};
}