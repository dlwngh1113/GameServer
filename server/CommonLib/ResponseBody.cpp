#include "pch.h"
#include "ResponseBody.h"

namespace Common
{
	ResponseBody::ResponseBody(Command type)
		: Packet((short)type)
	{
	}
	
	void ResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(code);
		ps.Write(message);
	}

	void ResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(code);
		ps.Read(message);
	}
}
