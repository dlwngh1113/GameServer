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
		memcpy_s(m_data.data(), m_data.size(), data, size);
	}

	void BaseCommandHandler::SendResponse(std::shared_ptr<Common::Packet> packet)
	{
		Common::PacketStream ps;
		std::string data = packet->Serialize(ps);

		m_peer->SendData(data);
	}
}