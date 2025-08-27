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

	void PacketStream::_Write(const void* pData, int32_t size)
	{
		const uint8_t* ptr = reinterpret_cast<const uint8_t*>(pData);
		m_buffer.insert(m_buffer.end(), ptr, ptr + size);
	}

	void PacketStream::_Read(void* pData, int32_t size)
	{
		memcpy(pData, m_buffer.data() + m_offset, size);
		m_offset += size;
	}

	std::string PacketStream::GetData(int16_t id, int16_t type)
	{
		Header header;
		header.type = type;
		header.id = id;
		header.size = static_cast<int16_t>(sizeof(Header) + m_buffer.size());

		uint8_t* ptr = reinterpret_cast<uint8_t*>(&header);
		m_buffer.insert(m_buffer.begin(), ptr, ptr + sizeof(header));

		return std::string(m_buffer.begin(), m_buffer.end());
	}

	void PacketStream::Write(const std::string& val)
	{
		int16_t size = static_cast<int16_t>(val.size());
		this->operator<<(size);
		_Write(&val[0], size);
	}

	void PacketStream::Read(std::string& val)
	{
		int16_t size;
		this->operator>>(size);
		val.resize(size);
		_Read(&val[0], size);
	}
}