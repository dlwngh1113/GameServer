#include "pch.h"
#include "Packet.h"

namespace Common
{
	void Packet::Serialize()
	{

	}

	template <typename T>
	Packet& Packet::operator<<(const T& val)
	{

	}

	template <>
	Packet& Packet::operator<<<string>(const string& val)
	{

	}

	template <typename T>
	Packet& Packet::operator>>(T& val)
	{

	}

	template <>
	Packet& Packet::operator>><string>(string& val)
	{

	}
}