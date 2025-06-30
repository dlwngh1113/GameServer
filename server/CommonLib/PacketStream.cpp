#include "pch.h"
#include "PacketStream.h"

namespace Common
{
	PacketStream::PacketStream()
		: m_offset(0)
	{
	}

	PacketStream::PacketStream(const uint8_t* data, uint64_t size)
		: m_offset(0)
		, m_buffer(data, data + size)
	{
	}

	std::string PacketStream::GetData(uint16_t id, uint16_t type)
	{
		Header header;
		header.type = type;
		header.id = id;
		header.size = static_cast<uint16_t>(sizeof(Header) + m_buffer.size());

		uint8_t* ptr = reinterpret_cast<uint8_t*>(&header);
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
		uint16_t size = static_cast<uint16_t>(val.size());
		this->operator<<(size);

		m_buffer.insert(m_buffer.end(), val.begin(), val.end());

		return *this;
	}

	template<>
	PacketStream& PacketStream::operator<<<float>(const float& val)
	{
		const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&val);
		m_buffer.insert(m_buffer.end(), ptr, ptr + sizeof(val));

		return *this;
	}

	template<>
	PacketStream& PacketStream::operator<<<int32_t>(const int32_t& val)
	{
		const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&val);
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
		uint16_t size;
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

	template<>
	PacketStream& PacketStream::operator>><int32_t>(int32_t& val)
	{
		memcpy_s(&val, sizeof(int32_t), m_buffer.data() + m_offset, sizeof(int32_t));
		m_offset += sizeof(int32_t);

		return *this;
	}
}