#include "pch.h"
#include "RingBuffer.h"

namespace Common
{
	RingBuffer::RingBuffer(int32_t bufferSize)
		: m_size(bufferSize)
		, m_data{ new uint8_t[m_size] }
		, m_writePos{ m_data }
		, m_readPos{ m_data }
	{
	}

	RingBuffer::~RingBuffer()
	{
		if (m_data)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}

	void RingBuffer::Pop(uint8_t* buffer, int32_t packetSize)
	{
		int32_t copySize = packetSize;
		if (m_readPos + copySize > m_writePos)
		{
			copySize = static_cast<int32_t>(m_writePos - m_readPos);
		}
		
		memcpy_s(buffer, copySize, m_readPos, copySize);
		m_readPos += copySize;
	}

	void RingBuffer::Peek(uint8_t* buffer, int32_t packetSize)
	{
		int32_t copySize = packetSize;
		if (m_readPos + copySize > m_writePos)
		{
			copySize = static_cast<int32_t>(m_writePos - m_readPos);
		}

		memcpy_s(buffer, copySize, m_readPos, copySize);
	}

	void RingBuffer::AddReceivedSize(int32_t receivedSize)
	{
		m_writePos += receivedSize;
	}

	const uint8_t* RingBuffer::GetReadBuffer() const
	{
		return m_readPos;
	}

	const int32_t RingBuffer::GetReadableSize() const
	{
		return static_cast<int32_t>(m_writePos - m_readPos);
	}

	uint8_t* RingBuffer::GetWriteBuffer()
	{
		// 패킷을 받을 만큼 충분한 공간이 없다면 가장 앞으로 데이터를 복사함
		if (m_writePos + (m_size / 4) > m_data + m_size)
		{
			int32_t leftSize = static_cast<int32_t>(m_writePos - m_readPos);
			memcpy_s(m_data, leftSize, m_readPos, leftSize);

			m_readPos = m_data;
			m_writePos = m_data + leftSize;
		}

		return m_writePos;
	}

	int32_t RingBuffer::GetWriteBufferSize() const
	{
		return static_cast<int32_t>((m_data + m_size) - m_writePos);
	}
}