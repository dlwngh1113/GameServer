#pragma once

namespace Core
{
	class RingBuffer
	{
		int32_t m_size;
		uint8_t* m_data;
		uint8_t* m_writePos;
		uint8_t* m_readPos;
		std::mutex m_lock;

	public:
		RingBuffer(int32_t bufferSize);
		virtual ~RingBuffer();

		void Pop(uint8_t* buffer, int32_t packetSize);
		void Peek(uint8_t* buffer, int32_t packetSize);

		void AddReceivedSize(int32_t receivedSize);

		const uint8_t* GetReadBuffer() const;
		const int32_t GetReadableSize() const;

		uint8_t* GetWriteBuffer();
		int32_t GetWriteBufferSize() const;
	};
}