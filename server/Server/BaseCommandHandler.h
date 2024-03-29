#pragma once
#include "Peer.h"

namespace Core
{
	class BaseCommandHandler
	{
	protected:
		shared_ptr<Peer> m_peer;
		Common::Header* m_header;

	public:
		BaseCommandHandler();
		virtual ~BaseCommandHandler();

		void Initialize(shared_ptr<Peer> peer, Common::Header* header);

		virtual void Handle() = 0;
	};
}