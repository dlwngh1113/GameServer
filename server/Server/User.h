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
	int m_moveTime{ };
	std::mutex m_lock;

public:
	explicit User(Core::Peer* peer);
	virtual ~User();

	// Properties
public:
	const std::string& userId() const { return m_userId; }
	const boost::uuids::uuid& id() const { return m_id; }
	float x() const { return m_x; }
	float y() const { return m_y; }
	int moveTime();
	void setMoveTime(int moveTime);

	// Member functions
public:
	void Login(std::shared_ptr<sql::ResultSet> user);
	void Teleport(float x, float y);
	void Move(float x, float y);
};