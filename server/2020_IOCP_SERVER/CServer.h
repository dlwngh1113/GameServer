#pragma once
#include "BaseApplication.h"
#include "Uuid.h"

class User;
class Core::Peer;

class CServer : public Core::BaseApplication
{
	std::mutex m_userLock;
	std::unordered_map<boost::uuids::uuid, std::shared_ptr<User>> m_users;

	static CServer s_instance;

private:
	void Initialize();

protected:
	void Release();

	virtual void OnAccepted(Core::Peer* peer) override;
	virtual void OnDisconnected(Core::Peer* peer) override;

public:
	CServer();
	CServer(boost::asio::io_context context);
	virtual ~CServer();
	CServer(const CServer& other) = delete;
	CServer& operator=(const CServer& other) = delete;

	virtual void Run() override;

	std::shared_ptr<User> GetUser(const boost::uuids::uuid& id);

	static CServer& GetInstance()
	{
		return s_instance;
	}
};