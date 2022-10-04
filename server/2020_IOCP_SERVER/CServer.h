#pragma once
#include"CUser.h"

class CServer
{
	HANDLE		h_iocp;

	SOCKET g_lSocket;
	OVER_EX g_accept_over;

	std::mutex m_userLock;
	std::unordered_map<int, CUser*> m_users;
public:
	CServer();
	virtual ~CServer();

	void run();
	void worker_thread();
	void CheckUserValidation(SOCKET ns);
	void AddNewClient(int idx);
	void disconnect_client(int id);
};