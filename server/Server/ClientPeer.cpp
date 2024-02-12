#include "stdafx.h"
#include "ClientPeer.h"
#include "BaseRequestHandlerFactory.h"
#include "BaseRequestHandler.h"
#include "BaseApplication.h"

namespace Core
{
	ClientPeer::ClientPeer(Peer* peer, BaseRequestHandlerFactory* instance)
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