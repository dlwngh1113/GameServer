#pragma once

namespace Core
{
	class Packet
	{
	private:
		vector<unsigned char> m_data;
		size_t m_offset;

	public:
		Packet();

	public:
		boost::asio::mutable_buffer Serialize();
		virtual void Deserialize() = 0;

	protected:
		// Serialize
		virtual void SerializeInternal() = 0;
		template <typename T>
		Packet* operator<<(const T& data);
		template <>
		Packet* operator<<<string>(const string& data);

		// Deserialize
		template <typename T>
		Packet* operator>>(T& data);
		template <>
		Packet* operator>><string>(string& data);
	};

	template <typename T>
	inline Packet* Packet::operator<<(const T& data)
	{
		memcpy_s(m_data.data() + m_offset, m_data.capacity(), (unsigned char*)&data, sizeof(T));
		m_offset += sizeof(T);

		return this;
	}

	template <>
	inline Packet* Packet::operator<<<string>(const string& data)
	{
		this->operator<<(data.size());

		memcpy_s(m_data.data() + m_offset, m_data.capacity(), data.data(), data.size());
		m_offset += data.size();

		return this;
	}

	template <typename T>
	inline Packet* Packet::operator>>(T& data)
	{
		data = *((T*)m_data.data() + m_offset);
		m_offset += sizeof(T);

		return this;
	}

	template <>
	inline Packet* Packet::operator>><string>(string& data)
	{
		size_t length;
		this->operator>>(length);

		data.resize(length);
		data.replace(data.begin(), data.end(), (const char*)(m_data.data() + m_offset));

		m_offset += length;

		return this;
	}
}
