#pragma once
#include"Place.h"
#include"BaseServer.h"

using namespace std;

class CServer : public BaseServer
{
	std::mutex m_userLock;
	std::unordered_map<SOCKET, shared_ptr<User>> m_users;

	static CServer* m_instance;

protected:
	void Release();

	void OnAccept(const SOCKET socket, shared_ptr<Peer> peer) override;
	void OnDisconnected(const SOCKET socket) override;

public:
	CServer();
	virtual ~CServer();

	void Run() override;
	void Init();

	shared_ptr<User> GetUser(SOCKET key);

	static CServer* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CServer;

		return m_instance;
	}
};