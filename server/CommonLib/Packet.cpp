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
		short size = sizeof(val);
		m_buffer.insert(m_buffer.end(), size, &val);

		m_offset += size;
	}

	template <>
	Packet& Packet::operator<<<string>(const string& val)
	{
		short size = val.size();
		this->operator<<(size);

		m_buffer.insert(m_buffer.end(), size, &val[0]);
	}

	template <typename T>
	Packet& Packet::operator>>(T& val)
	{

	}

	template <>
	Packet& Packet::operator>><string>(string& val)
	{

	}
}