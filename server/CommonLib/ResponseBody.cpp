#include "pch.h"
#include "ResponseBody.h"

namespace Common
{
	void ResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps << m_code << m_message;
	}

	void ResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> m_code >> m_message;
	}
	
	ResponseBody::ResponseBody(Command type)
		: Packet(type)
	{
	}
}
