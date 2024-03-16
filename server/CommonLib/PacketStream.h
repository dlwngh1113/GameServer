#pragma once

namespace Common
{
#pragma pack(push, 1)
	struct Header
	{
		short type;
		short size;
	};
#pragma pack(pop)

	class PacketStream
	{
	private:
		short m_offset;
		std::vector<unsigned char> m_buffer;

	public:
		explicit PacketStream();
		explicit PacketStream(const unsigned char* data, size_t size);

		std::string GetData(short type);

		template <typename T>
		PacketStream& operator<<(const T& val);

		template <>
		PacketStream& operator<<<std::string>(const std::string& val);

		template <typename T>
		PacketStream& operator>>(T& val);

		template <>
		PacketStream& operator>><std::string>(std::string& val);
	};
}
