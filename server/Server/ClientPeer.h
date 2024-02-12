#pragma once
#include "Peer.h"

namespace Core
{
	class BaseCommandHandlerFactory;
	
	class ClientPeer
	{
	protected:
		Peer* m_peer;

	public:
		explicit ClientPeer(Peer* peer, BaseCommandHandlerFactory* instance);
		virtual ~ClientPeer();

		const boost::uuids::uuid& GetID() const { return m_peer->id(); }

		void SendPacket(char* data, size_t size);
	};
}