#pragma once
#include "RequestHandlerException.h"

namespace Core
{
	class ClientPeer;

	class BaseRequestHandler
	{
	protected:
		ClientPeer* m_peer;
		ClientCommon::Header* m_header;

	public:
		BaseRequestHandler();
		virtual ~BaseRequestHandler();

		void Initialize(ClientPeer* peer, ClientCommon::Header* header);

		virtual void Handle() = 0;
	};
}