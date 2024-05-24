#pragma once
#include "Peer.h"

namespace Core
{
	class BaseCommandHandler
	{
	protected:
		std::shared_ptr<Peer> m_peer;
		std::vector<unsigned char> m_data;

	public:
		BaseCommandHandler();
		virtual ~BaseCommandHandler();

		void Initialize(std::shared_ptr<Peer> peer, unsigned char* data, size_t size);

		virtual void Handle() = 0;
	};
}