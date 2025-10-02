#include "pch.h"
#include "ResponseBody.h"

namespace Common
{
	ResponseBody::ResponseBody(Command type)
		: Packet((int16_t)type)
	{
	}

	ResponseBody::~ResponseBody()
	{
	}
	
	void ResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps << code << message;
	}

	void ResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> code >> message;
	}
}
