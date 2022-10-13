#pragma once
#include"CUser.h"
#include"BaseServer.h"

class CServer : public BaseServer
{
	HANDLE		h_iocp;

	SOCKET g_lSocket;
	OVER_EX g_accept_over;

	std::mutex m_userLock;
	std::unordered_map<int, CUser*> m_users;
protected:
	void Run() override;
	void Release() override;
public:
	CServer();
	virtual ~CServer();

	void run();
	void worker_thread();
	bool IsValidUser(SOCKET ns);
	void AddNewUser(int idx);
	void disconnect_client(int id);
};