#pragma once
#include "IPeer.h"
#include "OverlappedExtension.h"

#ifdef JCORE_EXPORTS
#define JCORE_API __declspec(dllexport)
#else
#define JCORE_API __declspec(dllimport)
#endif

class BaseRequestHandlerFactory;

namespace JCore
{
	class JCORE_API Peer : public IPeer
	{
	protected:
		SOCKET m_socket{ NULL };
		OverlappedExtension m_recvOver;
		std::mutex m_lock;

		unsigned char* m_pReceiveStartPtr{ NULL };

	private:
		void StartRecv();
		void ReceiveLeftData(unsigned char* pNextRecvPos);

	protected:
		virtual void OnProcessPacket(unsigned char* data, unsigned short snSize) = 0;

	public:
		explicit Peer(SOCKET socket);
		virtual ~Peer();

		int GetID() const { return static_cast<int>(m_socket); }

		void ProcessIO(DWORD ioSize) override final;
		void SendPacket(unsigned char* data, unsigned short snSize) override final;
	};
}