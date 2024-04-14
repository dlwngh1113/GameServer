#include "pch.h"
#include "ResponseBody.h"

namespace Common
{
	void ResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps << m_type << m_message;
	}

	void ResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> m_type >> m_message;
	}
}
