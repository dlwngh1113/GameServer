#pragma once
#include "BaseApplication.h"
#include "Place.h"
#include "Singleton.h"

class User;
#ifdef _WIN32
	class Core::Peer;
#endif // _WIN32


class CServer : public Core::BaseApplication, public Core::Singleton<CServer>
{
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
	virtual ~CServer();

	virtual void Run() override;

	Place* GetPlace() const { return m_place.get(); }
	std::shared_ptr<User> GetUser(const boost::uuids::uuid& id);
	const std::unordered_map<boost::uuids::uuid, std::shared_ptr<User>, Core::uuid_hash, Core::uuid_equal>& users() const { return m_users; }
};