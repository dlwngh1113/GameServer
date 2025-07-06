#pragma once

namespace Core
{
	class RingBuffer
	{
		uint8_t m_data[MAX_BUFFER]{};
		uint8_t* m_writePos;
		uint8_t* m_readPos;
		std::mutex m_lock;

	public:
		RingBuffer();

		void Pop(uint8_t* buffer, int32_t packetSize);
		boost::asio::mutable_buffers_1 GetBuffer();
	};
}