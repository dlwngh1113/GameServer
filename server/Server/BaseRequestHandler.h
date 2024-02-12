#pragma once
#include "RequestHandlerException.h"

namespace Core
{
	class Peer;

	class BaseRequestHandler
	{
	protected:
		shared_ptr<Peer> m_peer;
		ClientCommon::Header* m_header;

	public:
		BaseRequestHandler();
		virtual ~BaseRequestHandler();

		void Initialize(shared_ptr<Peer> peer, ClientCommon::Header* header);

		virtual void Handle() = 0;
	};
}