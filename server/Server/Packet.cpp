#include "stdafx.h"
#include "Packet.h"

namespace Core
{
	Packet::Packet()
		: m_offset(0)
	{
		m_data.reserve(MAX_BUFFER);
	}

	boost::asio::mutable_buffer Packet::Serialize()
	{
		SerializeInternal();
		return boost::asio::mutable_buffer(m_data.data(), m_data.size());
	}

	void Packet::Deserialize()
	{

	}
}