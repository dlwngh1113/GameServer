#pragma once
#include "ClientPeer.h"
#include "Uuid.h"

class ConnectionPool;

class User : public Core::ClientPeer, public std::enable_shared_from_this<User>
{
private:
	boost::uuids::uuid m_id{ Core::Uuid::Empty() };
	std::string m_userId{};
	float m_x{}, m_y{};

public:
	explicit User(Core::Peer* peer);
	virtual ~User();

	// Properties
public:
	const boost::uuids::uuid& id() const { return m_id; }
	float x() const { return m_x; }
	float y() const { return m_y; }

	// Member functions
public:
	void Login(std::shared_ptr<sql::ResultSet> user);
};