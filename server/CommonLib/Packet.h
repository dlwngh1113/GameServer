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
		vector<unsigned char> m_buffer;

	public:
		Packet();

	public:
		void Serialize();

		template <typename T>
		Packet& operator<<(const T& val);

		template <>
		Packet& operator<<<string>(const string& val);

		template <typename T>
		Packet& operator>>(T& val);

		template <>
		Packet& operator>><string>(string& val);
	};
}
