#pragma once
#include "Define.h"

namespace Common
{
#pragma pack(push, 1)
	struct COMMON_LIB_API Header
	{
		int16_t type;
		int16_t size;
		int16_t id;
	};
#pragma pack(pop)

	class COMMON_LIB_API PacketStream
	{
	private:
		int16_t m_offset;
		std::vector<uint8_t> m_buffer;

	public:
		explicit PacketStream();
		explicit PacketStream(const uint8_t* data, int32_t size);

	private:
		void _Write(const void* pData, int32_t size);
		void _Read(void* pData, int32_t size);

	public:
		std::string GetData(int16_t id, int16_t type);

		template <class T>
		PacketStream& operator<<(const T& val)
		{
			_Write(&val, sizeof(val));
			return *this;
		}

		void Write(const std::string& val);

		template <class T>
		PacketStream& operator>>(T& val)
		{
			_Read(&val, sizeof(val));
			return *this;
		}

		void Read(std::string& val);
	};
}
