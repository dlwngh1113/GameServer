#pragma once
#include "RequestHandlerException.h"

struct ClientCommon::BasePacket;

namespace Core
{
	class Peer;

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