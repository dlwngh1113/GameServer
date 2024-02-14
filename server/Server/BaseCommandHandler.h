#pragma once
#include "CommandHandlerException.h"

namespace Core
{
	class Peer;

	class BaseCommandHandler
	{
	protected:
		shared_ptr<Peer> m_peer;
		ClientCommon::Header* m_header;

	public:
		BaseCommandHandler();
		virtual ~BaseCommandHandler();

		void Initialize(shared_ptr<Peer> peer, ClientCommon::Header* header);

		virtual void Handle() = 0;
	};
}