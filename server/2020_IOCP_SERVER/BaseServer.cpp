#include "BaseServer.h"

BaseServer::BaseServer()
{

}

BaseServer::~BaseServer()
{
	Release();
}

void BaseServer::Run()
{
	std::wcout.imbue(std::locale("korean"));

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	m_listenSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_listenSocket), h_iocp, KEY_SERVER, 0);

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = ::htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	::bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	::listen(m_listenSocket, 5);

	SOCKET cSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_acceptOver.op_mode = OP_MODE_ACCEPT;
	m_acceptOver.wsa_buf.len = static_cast<int>(cSocket);
	ZeroMemory(&m_acceptOver.wsa_over, sizeof(&m_acceptOver.wsa_over));
	AcceptEx(m_listenSocket, cSocket, m_acceptOver.iocp_buf, 0, 32, 32, NULL, &m_acceptOver.wsa_over);

	std::vector<std::thread> worker_threads;
	for (int i = 0; i < MAX_THREAD_COUNT; ++i)
		worker_threads.emplace_back([&]() { Process(); });
	for (auto& th : worker_threads)
		th.join();
}

void BaseServer::Release()
{
	closesocket(m_listenSocket);
	::WSACleanup();
}

void BaseServer::OnAccept()
{
	SOCKET cSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_acceptOver.op_mode = OP_MODE_ACCEPT;
	m_acceptOver.wsa_buf.len = static_cast<int>(cSocket);
	ZeroMemory(&m_acceptOver.wsa_over, sizeof(&m_acceptOver.wsa_over));
	AcceptEx(m_listenSocket, cSocket, m_acceptOver.iocp_buf, 0, 32, 32, NULL, &m_acceptOver.wsa_over);
}
