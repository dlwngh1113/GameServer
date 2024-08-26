#pragma once
#include "BaseApplication.h"
#include "Place.h"

class User;
class Core::Peer;

class CServer : public Core::BaseApplication
{
	std::mutex m_userLock;
	std::unordered_map<boost::uuids::uuid, std::shared_ptr<User>, Core::uuid_hash, Core::uuid_equal> m_users;
	std::unique_ptr<Place> m_place;

private:
	void Initialize();

protected:
	virtual void OnTearDown() override;
	virtual void OnAccepted(Core::Peer* peer) override;
	virtual void OnDisconnected(Core::Peer* peer) override;

public:
	CServer();
	CServer(const CServer& other) = delete;
	CServer& operator=(const CServer& other) = delete;

	virtual void Run() override;

	Place* GetPlace() const { return m_place.get(); }
	std::shared_ptr<User> GetUser(const boost::uuids::uuid& id);
	const std::unordered_map<boost::uuids::uuid, std::shared_ptr<User>, Core::uuid_hash, Core::uuid_equal>& users() const { return m_users; }

private:
	static CServer s_instance;

public:
	static CServer& instance() { return s_instance; }
};