#include "stdafx.h"
#include "BaseCommandHandler.h"

namespace Core
{
	BaseCommandHandler::BaseCommandHandler()
		: m_peer{ nullptr }
	{
	}

	BaseCommandHandler::~BaseCommandHandler()
	{
	}

	void BaseCommandHandler::Initialize(std::shared_ptr<Peer> peer, unsigned char* data, size_t size)
	{
		m_peer = peer;
		m_data.resize(size);
		memcpy_s(&m_data[0], m_data.size(), data, size);
	}
}