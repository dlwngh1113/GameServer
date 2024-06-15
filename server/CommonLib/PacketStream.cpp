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

	std::string PacketStream::GetData(short id, short type)
	{
		Header header;
		header.type = type;
		header.id = id;
		header.size = static_cast<short>(sizeof(Header) + m_buffer.size());

		unsigned char* ptr = reinterpret_cast<unsigned char*>(&header);
		m_buffer.insert(m_buffer.begin(), ptr, ptr + sizeof(header));

		return std::string(m_buffer.begin(), m_buffer.end());
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

	template<>
	PacketStream& PacketStream::operator<<<float>(const float& val)
	{
		const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&val);
		m_buffer.insert(m_buffer.end(), ptr, ptr + sizeof(val));

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
		memcpy_s(&val[0], size, m_buffer.data() + m_offset, size);

		m_offset += size;

		return *this;
	}

	template<>
	PacketStream& PacketStream::operator>><float>(float& val)
	{
		memcpy_s(&val, sizeof(float), m_buffer.data() + m_offset, sizeof(float));
		m_offset += sizeof(float);

		return *this;
	}
}