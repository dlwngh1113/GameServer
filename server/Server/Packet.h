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
		ostream& operator<<(const T& data);
		template <>
		ostream& operator<<<string>(const string& data);

		// Deserialize
		template <typename T>
		istream& operator>>(T& data);
		template <>
		istream& operator>><string>(string& data);
	};

	template <typename T>
	inline ostream& Packet::operator<<(const T& data)
	{
		memcpy_s(m_data.data() + m_offset, m_data.capacity(), (unsigned char*)&data, sizeof(T));
		m_offset += sizeof(T);
	}

	template <>
	inline ostream& Packet::operator<<<string>(const string& data)
	{
		this->operator<<(data.size());

		memcpy_s(m_data.data() + m_offset, m_data.capacity(), data.data(), data.size());
		m_offset += data.size();
	}

	template <typename T>
	inline istream& Packet::operator>>(T& data)
	{
		data = *((T*)m_data.data() + m_offset);
		m_offset += sizeof(T);
	}

	template <>
	inline istream& Packet::operator>><string>(string& data)
	{
		size_t length;
		this->operator>>(length);

		data.resize(length);
		data.replace(data.begin(), data.end(), (const char*)(m_data.data() + m_offset));

		m_offset += length;
	}
}
