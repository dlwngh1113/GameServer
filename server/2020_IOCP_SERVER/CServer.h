#pragma once
#include "BaseServer.h"

class User;
class Peer;

class CServer : public BaseServer
{
	std::mutex m_userLock;
	std::unordered_map<SOCKET, std::shared_ptr<User>> m_users;

	static CServer* s_instance;

private:
	void Initialize();

protected:
	void Release();

	void OnAccept(const SOCKET socket, std::shared_ptr<Peer> peer) override;
	void OnDisconnected(const SOCKET socket) override;

public:
	CServer();
	virtual ~CServer();

	void Run() override;

	std::shared_ptr<User> GetUser(SOCKET key);

	static CServer* GetInstance()
	{
		if (s_instance == nullptr)
			s_instance = new CServer;

		return s_instance;
	}
};