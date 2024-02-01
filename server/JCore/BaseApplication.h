#pragma once
#include "Peer.h"

#ifdef JCORE_EXPORTS
#define JCORE_API __declspec(dllexport)
#else
#define JCORE_API __declspec(dllimport)
#endif

namespace JCore
{
	class JCORE_API BaseApplication
	{
		HANDLE h_iocp;
		SOCKET m_listenSocket;
		OverlappedExtension m_acceptOver;

		std::mutex m_clientLock;
		std::unordered_map<SOCKET, std::shared_ptr<Peer>> m_peers;
	private:
		void Initialize();
		void Listen();
		void BeginAcceptPeer();

		void AddNewClient(SOCKET socket);
		void DisconnectClient(SOCKET socket);

	protected:
		void Process();
		void Release();

		virtual void OnAccept(const SOCKET socket, Peer* peer) = 0;
		virtual void OnDisconnected(const SOCKET socket) = 0;

	public:
		BaseServer();
		virtual ~BaseServer();

		virtual void Run();
	};
}