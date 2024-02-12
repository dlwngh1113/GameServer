#pragma once
#include "BaseApplication.h"

class User;
class Core::Peer;

class CServer : public Core::BaseApplication
{
	mutex m_userLock;
	unordered_map<boost::uuids::uuid, shared_ptr<User>, Core::uuid_hash, Core::uuid_equal> m_users;

	static CServer s_instance;

private:
	void Initialize();

protected:
	void Release();

	virtual void OnAccepted(Core::Peer* peer) override;
	virtual void OnDisconnected(Core::Peer* peer) override;

public:
	CServer();
	virtual ~CServer();
	CServer(const CServer& other) = delete;
	CServer& operator=(const CServer& other) = delete;

	virtual void Run() override;

	shared_ptr<User> GetUser(const boost::uuids::uuid& id);

	static CServer& GetInstance()
	{
		return s_instance;
	}
};