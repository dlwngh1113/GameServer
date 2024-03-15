#include "pch.h"
#include "Packet.h"

namespace Common
{
	Packet::Packet()
		: m_type(0)
		, m_offset(0)
	{
	}

	Packet::Packet(short type, const unsigned char* ptr)
		: m_type(type)
		, m_offset(0)
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

	template <typename T>
	Packet& Packet::operator<<(const T& val)
	{
		const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&val);
		m_buffer.insert(m_buffer.end(), ptr, ptr + sizeof(val));

		return *this;
	}

	template <>
	Packet& Packet::operator<<<std::string>(const std::string& val)
	{
		short size = static_cast<short>(val.size());
		this->operator<<(size);

		m_buffer.insert(m_buffer.end(), val.begin(), val.end());

		return *this;
	}

	template <typename T>
	Packet& Packet::operator>>(T& val)
	{
		memcpy_s(&val, sizeof(T), m_buffer.data() + m_offset, sizeof(T));
		m_offset += sizeof(T);

		return *this;
	}

	template <>
	Packet& Packet::operator>><std::string>(std::string& val)
	{
		short size;
		this->operator>>(size);

		val.resize(size);
		memcpy_s(&val[0], size, (m_buffer.data() + m_offset), size);

		m_offset += size;

		return *this;
	}
}