#include "stdafx.h"
#include "RingBuffer.h"
#include "Logger.h"

namespace Core
{
	RingBuffer::RingBuffer()
		: m_writePos{ m_data }
		, m_readPos{ m_data }
	{
	}

	void RingBuffer::Pop(uint8_t* buffer, int32_t packetSize)
	{
		std::lock_guard lock{ m_lock };
		int32_t copySize = packetSize;
		if (m_writePos + copySize > m_readPos)
		{
			Logger::instance().Log(std::format("provided copySize {} CopyableSize", copySize, m_readPos - m_writePos));
			copySize = static_cast<int32_t>(m_readPos - m_writePos);
		}	
		
		memcpy_s(buffer, copySize, m_writePos, copySize);
		m_writePos += copySize;
	}

	boost::asio::mutable_buffers_1 RingBuffer::GetBuffer()
	{
		return boost::asio::buffer(m_writePos, (m_data + MAX_BUFFER) - m_writePos);
	}
}