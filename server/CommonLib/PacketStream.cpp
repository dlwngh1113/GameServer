#include "pch.h"
#include "PacketStream.h"

namespace Common
{
	PacketStream::PacketStream()
		: m_offset(0)
	{
	}

	PacketStream::PacketStream(const unsigned char* data, size_t size)
		: m_offset(0)
		, m_buffer(data, data + size)
	{
	}

	template <typename T>
	PacketStream& PacketStream::operator<<(const T& val)
	{
		const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&val);
		m_buffer.insert(m_buffer.end(), ptr, ptr + sizeof(val));

		return *this;
	}

	template <>
	PacketStream& PacketStream::operator<<<std::string>(const std::string& val)
	{
		short size = static_cast<short>(val.size());
		this->operator<<(size);

		m_buffer.insert(m_buffer.end(), val.begin(), val.end());

		return *this;
	}

	template <typename T>
	PacketStream& PacketStream::operator>>(T& val)
	{
		memcpy_s(&val, sizeof(T), m_buffer.data() + m_offset, sizeof(T));
		m_offset += sizeof(T);

		return *this;
	}

	template <>
	PacketStream& PacketStream::operator>><std::string>(std::string& val)
	{
		short size;
		this->operator>>(size);

		val.resize(size);
		memcpy_s(&val[0], size, (m_buffer.data() + m_offset), size);

		m_offset += size;

		return *this;
	}
}