#include "stdafx.h"
#include "Packet.h"

namespace Core
{
	Packet::Packet()
		: m_offset(0)
	{
		m_data.reserve(MAX_BUFFER);

		this->operator<<((short)0)->operator<<((size_t)0);
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