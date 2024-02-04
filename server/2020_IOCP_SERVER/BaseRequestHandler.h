#pragma once
#include "RequestHandlerException.h"

class Core::Peer;
struct ClientCommon::BasePacket;

namespace Core
{
	class BaseRequestHandler
	{
	protected:
		Peer* m_peer;
		ClientCommon::BasePacket* m_packet;

	public:
		BaseRequestHandler();
		virtual ~BaseRequestHandler();

		void Initialize(Peer* peer, ClientCommon::BasePacket* packet);

		virtual void Handle() = 0;
	};
}