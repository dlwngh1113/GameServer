#include "stdafx.h"
#include "BaseCommandHandler.h"

namespace Core
{
	BaseCommandHandler::BaseCommandHandler()
		: m_header{ nullptr }
		, m_peer{ nullptr }
	{
	}

	BaseCommandHandler::~BaseCommandHandler()
	{
	}

	void BaseCommandHandler::Initialize(std::shared_ptr<Peer> peer, Common::Header* header)
	{
		m_peer = peer;
		m_header = header;
	}
}