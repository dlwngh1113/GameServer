#pragma once
#include "BaseServer.h"

class User;
class Peer;

class CServer : public BaseServer
{
	std::mutex m_userLock;
	std::unordered_map<SOCKET, std::shared_ptr<User>> m_users;

	static CServer s_instance;

private:
	CServer();
	void Initialize();

protected:
	void Release();

	void OnAccept(const SOCKET socket, Peer* peer) override;
	void OnDisconnected(const SOCKET socket) override;

public:
	virtual ~CServer();
	CServer(const CServer& other) = delete;
	CServer& operator=(const CServer& other) = delete;

	void Run() override;

	std::shared_ptr<User> GetUser(SOCKET key);

	static CServer& GetInstance()
	{
		return s_instance;
	}
};