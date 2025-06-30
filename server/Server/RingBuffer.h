#pragma once

namespace Core
{
	class RingBuffer
	{
		uint8_t m_data[MAX_BUFFER];
		uint8_t* m_currentPos;
		std::mutex m_lock;

	public:
		RingBuffer();

		void Pop(uint8_t* buffer, uint32_t packetSize);
	};
}