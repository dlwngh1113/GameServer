#pragma once

namespace Common
{
	class PacketStream
	{
	private:
		short m_offset;
		std::vector<unsigned char> m_buffer;

	public:
		explicit PacketStream();
		explicit PacketStream(const unsigned char* data, size_t size);

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
