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
		explicit PacketStream(const uint8_t* data, uint64_t size);

		std::string GetData(int16_t id, int16_t type);

		template <class T>
		void Write(const T& val);

		void Write(const std::string& val);

		template <class T>
		void Read(T& val);

		void Read(std::string& val);
	};
}
