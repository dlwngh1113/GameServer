#include "stdafx.h"
#include "ClientPeer.h"
#include "BaseRequestHandlerFactory.h"

namespace Core
{
	ClientPeer::ClientPeer(Peer* peer, BaseRequestHandlerFactory* instance) : m_peer{ peer }
	{
		m_factory = instance;
	}

	ClientPeer::~ClientPeer()
	{
	}

	void ClientPeer::SendPacket(ClientCommon::BasePacket* packet)
	{
	}
}