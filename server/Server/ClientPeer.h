#pragma once
#include "Peer.h"

namespace Core
{
	class BaseRequestHandlerFactory;
	
	class ClientPeer
	{
	protected:
		Peer* m_peer;
		BaseRequestHandlerFactory* m_factory;

	public:
		explicit ClientPeer(Peer* peer, BaseRequestHandlerFactory* instance);
		virtual ~ClientPeer();

		const boost::uuids::uuid& GetID() const { return m_peer->id(); }

		virtual void ProcessPacket(char* data, size_t size);
		void SendPacket(char* data, size_t size);
	};
}