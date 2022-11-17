#pragma once
#include"User.h"
#include"BaseServer.h"

class CServer : public BaseServer
{
	std::mutex m_userLock;
	std::unordered_map<SOCKET, User*> m_users;

	static CServer* m_instance;

protected:
	void OnAccept(const SOCKET socket, Peer*& peer) override;
	void OnDisconnected(SOCKET socket) override;

public:
	CServer();
	virtual ~CServer();

	void Run() override;
	void Init();

	User* GetUser(SOCKET key);

	static CServer* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CServer;

		return m_instance;
	}
};