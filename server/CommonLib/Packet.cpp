#include "pch.h"
#include "Packet.h"

namespace Common
{
	Packet::Packet()
		: m_type(0)
		, m_offset(0)
	{
	}

	void Packet::Serialize()
	{

	}

	template <typename T>
	Packet& Packet::operator<<(const T& val)
	{
		const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&val);
		m_buffer.insert(m_buffer.end(), ptr, ptr + sizeof(val));
	}

	template <>
	Packet& Packet::operator<<<string>(const string& val)
	{
		short size = static_cast<short>(val.size());
		this->operator<<(size);

		m_buffer.insert(m_buffer.end(), val.begin(), val.end());
	}

	template <typename T>
	Packet& Packet::operator>>(T& val)
	{
		memcpy_s(&val, sizeof(T), m_buffer.data() + m_offset, sizeof(T));
		m_offset += sizeof(T);
	}

	template <>
	Packet& Packet::operator>><string>(string& val)
	{
		short size;
		this->operator>>(size);

		val.resize(size);
		memcpy_s(&val[0], size, (m_buffer.data() + m_offset), size);

		m_offset += size;
	}
}