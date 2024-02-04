#pragma once
#include "BaseApplication.h"

class User;
class Core::Peer;

class CServer : public Core::BaseApplication
{
	std::mutex m_userLock;
	std::unordered_map<SOCKET, std::shared_ptr<User>> m_users;

	static CServer s_instance;

private:
	virtual void Initialize() override;

protected:
	void Release();

	virtual void OnAccepted(Core::Peer* peer) override;
	virtual void OnDisconnected(const SOCKET socket) override;

public:
	CServer(boost::asio::io_context context);
	virtual ~CServer();
	CServer(const CServer& other) = delete;
	CServer& operator=(const CServer& other) = delete;

	virtual void Run() override;

	std::shared_ptr<User> GetUser(SOCKET key);

	static CServer& GetInstance()
	{
		return s_instance;
	}
};