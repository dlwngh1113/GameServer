#include "CServer.h"

void CServer::Run()
{
}

void CServer::Release()
{
}

CServer::CServer()
{
}

CServer::~CServer()
{
}

void CServer::run()
{
	std::wcout.imbue(std::locale("korean"));

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	g_lSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(g_lSocket), h_iocp, KEY_SERVER, 0);

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = ::htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	::bind(g_lSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	::listen(g_lSocket, 5);

	SOCKET cSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	g_accept_over.op_mode = OP_MODE_ACCEPT;
	g_accept_over.wsa_buf.len = static_cast<int>(cSocket);
	ZeroMemory(&g_accept_over.wsa_over, sizeof(&g_accept_over.wsa_over));
	AcceptEx(g_lSocket, cSocket, g_accept_over.iocp_buf, 0, 32, 32, NULL, &g_accept_over.wsa_over);

	std::vector <std::thread> worker_threads;
	for (int i = 0; i < 6; ++i)
		worker_threads.emplace_back([&]() {worker_thread(); });
	for (auto& th : worker_threads)
		th.join();

	closesocket(g_lSocket);
	::WSACleanup();
}

void error_display(const char* msg, int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("%s[%d]: ", msg, err_no);
	std::wcout << lpMsgBuf << std::endl;
	while (true);
	LocalFree(lpMsgBuf);
}

void CServer::worker_thread()
{
	// 반복
	//   - 이 쓰레드를 IOCP thread pool에 등록  => GQCS
	//   - iocp가 처리를 맞긴 I/O완료 데이터를 꺼내기 => GQCS
	//   - 꺼낸 I/O완료 데이터를 처리
	while (true) {
		DWORD io_size;
		int key;
		ULONG_PTR iocp_key;
		WSAOVERLAPPED* lpover;
		int ret = 
		GetQueuedCompletionStatus(h_iocp, &io_size, &iocp_key, &lpover, INFINITE);
		key = static_cast<int>(iocp_key);
		// cout << "Completion Detected" << endl;
		if (FALSE == ret) {
			//error_display("GQCS Error", WSAGetLastError());
		}

		OVER_EX* over_ex = reinterpret_cast<OVER_EX*>(lpover);
		switch (over_ex->op_mode) {
		case OP_MODE_ACCEPT:
		{
			SOCKET ns = static_cast<SOCKET>(over_ex->wsa_buf.len);
			if (IsValidUser(ns))
				AddNewUser(ns);
		}
			break;
		case OP_MODE_RECV:
			if (0 == io_size)
				disconnect_client(key);
			else {
				//std::cout << "Packet from Client [" << key << "] - ioSize: " << io_size << "\"\n";
				//process_recv(key, io_size);
			}
			break;
		case OP_MODE_SEND:
			delete over_ex;
			break;
		}
	}
}

bool CServer::IsValidUser(SOCKET ns)
{
	if (MAX_USER <= m_users.size())
	{
		std::cout << "Max user limit exceeded." << std::endl;
		closesocket(ns);
	}
	else
	{
		int cnt;
		m_userLock.lock();
		for (cnt = 0; cnt < INT_MAX; ++cnt)
		{
			if (0 == m_users.count(cnt))
			{
				m_userLock.unlock();
				return true;
			}
			else
			{
				//m_useres[i]가 접속중일경우 해제
				if (m_users[cnt]->GetUserState() != UserState::LOGINBEGIN)
				{
					std::cout << "이미 로그인중이거나 로그인 한 사용자입니다.\n";
					m_userLock.unlock();
					break;
				}
			}
		}
		m_userLock.unlock();
	}
	return false;
}

void CServer::AddNewUser(int cnt)
{
	CUser* client = new CUser();
	m_users[cnt] = client;
	//CreateIoCompletionPort(reinterpret_cast<HANDLE>(ns), h_iocp, cnt, 0);
	client->InitIO();

	SOCKET cSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	g_accept_over.op_mode = OP_MODE_ACCEPT;
	g_accept_over.wsa_buf.len = static_cast<ULONG> (cSocket);
	ZeroMemory(&g_accept_over.wsa_over, sizeof(&g_accept_over.wsa_over));
	AcceptEx(g_lSocket, cSocket, g_accept_over.iocp_buf, 0, 32, 32, NULL, &g_accept_over.wsa_over);
}

void CServer::disconnect_client(int id)
{
	//auto client = reinterpret_cast<CUser*>(m_users[id]);
	//for (auto i = m_users.begin(); i != m_users.end(); ++i)
	//{
	//	if (i->first < MAX_USER)
	//	{
	//		if (i->first != id)
	//		{
	//			if (0 != i->second->GetViewlist().count(id))
	//			{
	//				i->second->GetViewlist().erase(id);
	//				reinterpret_cast<CClient*>(i->second)->ErasePlayer(id);
	//			}
	//		}
	//	}
	//}

	//client->GetInfo()->c_lock.lock();
	//client->Release();
	//client->GetInfo()->c_lock.unlock();
}