#include "stdafx.h"
#include "ClientPeer.h"
#include "BaseCommandHandlerFactory.h"

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

	void ClientPeer::SendPacket(Common::Packet* packet)
	{
		// Increase packet id
		packet->id++;

		// Serialize packet
		Common::PacketStream ps;
		std::string data = packet->Serialize(ps);

		m_peer->SendData(data.data(), data.size());
	}

	void ClientPeer::SendPacket(char* data, size_t size)
	{
		m_peer->SendData(data, size);
	}
}