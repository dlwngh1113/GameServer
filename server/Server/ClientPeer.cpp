#include "stdafx.h"
#include "ClientPeer.h"
#include "BaseCommandHandlerFactory.h"
#include "BaseCommandHandler.h"
#include "BaseApplication.h"

namespace Core
{
	ClientPeer::ClientPeer(Peer* peer, BaseCommandHandlerFactory* instance)
		: m_peer(peer)
	{
		m_peer->SetFactory(instance);
	}

	ClientPeer::~ClientPeer()
	{
	}

	void ClientPeer::SendPacket(char* data, size_t size)
	{
		m_peer->SendData(data, size);
	}
}