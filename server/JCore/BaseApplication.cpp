#include "pch.h"
#include "BaseApplication.h"

namespace JCore
{
	BaseApplication::BaseApplication()
	{
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2, 0), &WSAData);

		Initialize();
		Listen();
		BeginAcceptPeer();
	}

	void BaseApplication::Initialize()
	{
		h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
		m_listenSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_listenSocket), h_iocp, KEY_SERVER, 0);
	}

	void BaseApplication::Listen()
	{
		// IPv4, 서버 포트 설정
		SOCKADDR_IN serverAddr;
		memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = ::htons(SERVER_PORT);
		serverAddr.sin_addr.s_addr = INADDR_ANY;

		// 바인딩, 소켓IO 리스닝
		::bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
		::listen(m_listenSocket, 5);
	}

	void BaseApplication::BeginAcceptPeer()
	{
		SOCKET cSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		m_acceptOver.opMode = OP_ACCEPT;
		m_acceptOver.wsaBuf.len = static_cast<int>(cSocket);
		ZeroMemory(&m_acceptOver.wsaOver, sizeof(m_acceptOver.wsaOver));
		AcceptEx(m_listenSocket, cSocket, m_acceptOver.iocpBuf, 0, 32, 32, NULL, &m_acceptOver.wsaOver);
	}

	BaseApplication::~BaseApplication()
	{
		Release();
	}

	void BaseApplication::Release()
	{
		m_peers.clear();

		closesocket(m_listenSocket);

		::WSACleanup();
	}

	void BaseApplication::Run()
	{
		std::vector<std::thread> worker_threads;
		for (int i = 0; i < MAX_THREAD_COUNT; ++i)
			worker_threads.emplace_back([&]() { Process(); });
		for (auto& th : worker_threads)
			th.join();
	}

	void BaseApplication::AddNewClient(SOCKET socket)
	{
		// iocp에 소켓을 등록
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket), h_iocp, socket, 0);

		//객체 생성 후 관리
		std::shared_ptr<Peer> peer = std::make_shared<Peer>(socket);

		std::unique_lock<std::mutex> lock{ m_clientLock };
		m_peers.insert(std::pair<SOCKET, std::shared_ptr<Peer>>(socket, peer));
		lock.unlock();

		OnAccept(socket, peer.get());
		BeginAcceptPeer();
	}

	void BaseApplication::DisconnectClient(SOCKET socket)
	{
		std::unique_lock<std::mutex> lock{ m_clientLock };

		std::shared_ptr<Peer> toRemovePeer;
		auto result = m_peers.find(socket);
		if (result != m_peers.end())
		{
			toRemovePeer = result->second;
			m_peers.erase(socket);
		}
		lock.unlock();

		//LogFormat("Client Id : %d Successfully disconnected!", socket);

		OnDisconnected(socket);
	}

	void BaseApplication::Process()
	{
		// 반복
		//   - 이 쓰레드를 IOCP thread pool에 등록  => GQCS
		//   - iocp가 처리를 맞긴 I/O완료 데이터를 꺼내기 => GQCS
		//   - 꺼낸 I/O완료 데이터를 처리
		while (true)
		{
			DWORD ioSize;
			SOCKET ns;
			ULONG_PTR iocpKey;
			WSAOVERLAPPED* lpOver;
			int ret = GetQueuedCompletionStatus(h_iocp, &ioSize, &iocpKey, &lpOver, INFINITE);
			ns = static_cast<SOCKET>(iocpKey);
			if (FALSE == ret)
			{
				//error_display("GQCS Error", WSAGetLastError());
			}

			OverlappedExtension* overEx = reinterpret_cast<OverlappedExtension*>(lpOver);
			switch (overEx->opMode)
			{
			case OP_ACCEPT:
				ns = static_cast<SOCKET>(overEx->wsaBuf.len);
				AddNewClient(ns);
				break;
			case OP_RECV:
				if (0 == ioSize)
					DisconnectClient(ns);
				else
				{
					//LogFormat("Packet from Client [%d] - ioSize: %d", ns, ioSize);

					std::shared_ptr<Peer> peer = nullptr;
					std::unique_lock<std::mutex> lock{ m_clientLock };
					auto result = m_peers.find(ns);
					if (result != m_peers.end())
						peer = result->second;
					lock.unlock();

					if (!peer)
						peer->ProcessIO(ioSize);
				}
				break;
			case OP_SEND:
				delete overEx;
				//Global::GetInstance().overlappedPool.PushObject(overEx);
				break;
			}
		}
	}
}