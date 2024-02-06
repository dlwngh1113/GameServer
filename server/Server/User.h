#pragma once
#include "ClientPeer.h"

class ConnectionPool;

class User : public Core::ClientPeer, public std::enable_shared_from_this<User>
{
public:
	explicit User(Core::Peer* peer);
	virtual ~User();
};