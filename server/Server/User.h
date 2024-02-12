#pragma once
#include "ClientPeer.h"

class ConnectionPool;

class User : public Core::ClientPeer, public enable_shared_from_this<User>
{
	boost::uuids::uuid m_id;
public:
	explicit User(Core::Peer* peer);
	virtual ~User();

public:
	const boost::uuids::uuid& id() const { return m_id; }
};