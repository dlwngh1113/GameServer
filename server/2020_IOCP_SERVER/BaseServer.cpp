#include"stdafx.h"
#include "BaseServer.h"

BaseServer::BaseServer()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	Init();
	Listen();
}

BaseServer::~BaseServer()
{
	Release();
}

void BaseServer::Run()
{
	std::vector<std::thread> worker_threads;
	for (int i = 0; i < MAX_THREAD_COUNT; ++i)
		worker_threads.emplace_back([&]() { Process(); });
	for (auto& th : worker_threads)
		th.join();
}

void BaseServer::Init()
{
	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	m_listenSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_listenSocket), h_iocp, KEY_SERVER, 0);
}

void BaseServer::Listen()
{
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = ::htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	::bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	::listen(m_listenSocket, 5);

	BeginAcceptPeer();
}

void BaseServer::AddNewClient(SOCKET socket)
{
	// iocp에 소켓을 등록
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket), h_iocp, socket, 0);

	//객체 생성 후 관리
	Peer* peer = new Peer(socket);

	clientLock.lock();
	m_peers[socket] = peer;
	clientLock.unlock();
	
	OnAccept(socket, peer);
	BeginAcceptPeer();
}

void BaseServer::DisconnectClient(SOCKET socket)
{
	clientLock.lock();
	Peer* toRemovePeer = m_peers[socket];
	m_peers.erase(socket);
	clientLock.unlock();

	Logger::Info("Client id " + std::to_string(toRemovePeer->GetID()) + " successfully disconnected!");

	OnDisconnected(socket);

	if (toRemovePeer)
		delete toRemovePeer;
}

void BaseServer::Process()
{
	// 반복
	//   - 이 쓰레드를 IOCP thread pool에 등록  => GQCS
	//   - iocp가 처리를 맞긴 I/O완료 데이터를 꺼내기 => GQCS
	//   - 꺼낸 I/O완료 데이터를 처리
	while (true) {
		DWORD ioSize;
		SOCKET ns;
		ULONG_PTR iocpKey;
		WSAOVERLAPPED* lpOver;
		int ret =
			GetQueuedCompletionStatus(h_iocp, &ioSize, &iocpKey, &lpOver, INFINITE);
		ns = static_cast<SOCKET>(iocpKey);
		if (FALSE == ret) {
			//error_display("GQCS Error", WSAGetLastError());
		}

		OVER_EX* overEx = reinterpret_cast<OVER_EX*>(lpOver);
		switch (overEx->op_mode) {
		case OP_MODE_ACCEPT:
			ns = static_cast<SOCKET>(overEx->wsa_buf.len);
			AddNewClient(ns);
			break;
		case OP_MODE_RECV:
			if (0 == ioSize)
				DisconnectClient(ns);
			else
			{
				Logger::Info("Packet from Client [" + std::to_string(ns) + "] - ioSize: " + std::to_string(ioSize));
				clientLock.lock();
				m_peers[ns]->ProcessIO(ioSize);
				clientLock.unlock();
			}
			break;
		case OP_MODE_SEND:
			Statics::overlappedPool.PushObject(overEx);
			break;
		}
	}
}

void BaseServer::Release()
{
	for (auto& pair : m_peers)
		delete pair.second;
	m_peers.clear();

	closesocket(m_listenSocket);

	::WSACleanup();
}

void BaseServer::BeginAcceptPeer()
{
	SOCKET cSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_acceptOver.op_mode = OP_MODE_ACCEPT;
	m_acceptOver.wsa_buf.len = static_cast<int>(cSocket);
	ZeroMemory(&m_acceptOver.wsa_over, sizeof(&m_acceptOver.wsa_over));
	AcceptEx(m_listenSocket, cSocket, m_acceptOver.iocp_buf, 0, 32, 32, NULL, &m_acceptOver.wsa_over);
}