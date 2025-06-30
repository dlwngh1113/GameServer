#include "stdafx.h"
#include "RingBuffer.h"

namespace Core
{
	RingBuffer::RingBuffer()
	{

	}

	void RingBuffer::Pop(uint8_t* buffer, uint32_t packetSize)
	{
		std::lock_guard lock{ m_lock };
		memcpy_s(buffer, packetSize, m_currentPos, packetSize);

		m_currentPos += packetSize;
	}
}