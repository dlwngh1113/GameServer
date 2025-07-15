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

		template <typename T>
		PacketStream& operator<<(const T& val);

		template <>
		PacketStream& operator<<<std::string>(const std::string& val);

		template<>
		PacketStream& operator<<<float>(const float& val);

		template<>
		PacketStream& operator<<<int32_t>(const int32_t& val);

		template <typename T>
		PacketStream& operator>>(T& val);

		template <>
		PacketStream& operator>><std::string>(std::string& val);

		template<>
		PacketStream& operator>><float>(float& val);

		template<>
		PacketStream& operator>><int32_t>(int32_t& val);
	};
}
