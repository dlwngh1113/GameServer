#pragma once
#include"User.h"
#include"BaseServer.h"

class CServer : public BaseServer
{
	std::mutex m_userLock;
	std::unordered_map<SOCKET, User*> m_users;

protected:

	void OnAccept(const SOCKET socket, ClientPeer*& peer) override;

public:
	CServer();
	virtual ~CServer();

	void Run() override;
	void Init();
};