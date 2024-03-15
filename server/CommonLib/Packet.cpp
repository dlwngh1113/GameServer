#include "pch.h"
#include "Packet.h"

namespace Common
{
	Packet::Packet()
		: m_type(0)
	{
	}

	Packet::Packet(short type, const unsigned char* ptr)
		: m_type(type)
	{
	}

	std::string Packet::Serialize()
	{
		SerializeInternal();

		Header header;
		header.type = m_type;
		header.size = static_cast<short>(sizeof(Header) + m_buffer.size());

		unsigned char* ptr = reinterpret_cast<unsigned char*>(&header);
		m_buffer.insert(m_buffer.begin(), ptr, ptr + sizeof(header));

		return std::string(m_buffer.begin(), m_buffer.end());
	}

	void Packet::Deserialize()
	{
		Header header;
		this->operator>>(header);

		DeserializeInternal();
	}
}