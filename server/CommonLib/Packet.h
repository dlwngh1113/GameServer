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

	public:
		explicit Packet();
		explicit Packet(short type, const unsigned char* ptr);

	public:
		virtual std::string Serialize() final;
		virtual void Deserialize() final;

	protected:
		virtual void SerializeInternal() = 0;
		virtual void DeserializeInternal() = 0;
	};
}
