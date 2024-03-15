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

	class Packet
	{
	protected:
		short m_type;
		short m_offset;
		std::vector<unsigned char> m_buffer;

	public:
		explicit Packet();
		explicit Packet(short type, const unsigned char* ptr);

	public:
		virtual std::string Serialize() final;
		virtual void Deserialize() final;

	protected:
		virtual void SerializeInternal() = 0;
		virtual void DeserializeInternal() = 0;

		template <typename T>
		Packet& operator<<(const T& val);

		template <>
		Packet& operator<<<std::string>(const std::string& val);

		template <typename T>
		Packet& operator>>(T& val);

		template <>
		Packet& operator>><std::string>(std::string & val);
	};
}
