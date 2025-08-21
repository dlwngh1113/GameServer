#include "pch.h"
#include "TeleportCommandBody.h"

namespace Common
{
	TeleportCommandBody::TeleportCommandBody()
		: CommandBody(Command::Teleport)
	{
	}

	void TeleportCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(x);
		ps.Write(y);
	}

	void TeleportCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(x);
		ps.Read(y);
	}

	TeleportResponseBody::TeleportResponseBody()
		: ResponseBody(Command::Teleport)
	{
	}

	void TeleportResponseBody::SerializeInternal(PacketStream& ps)
	{
	}

	void TeleportResponseBody::DeserializeInternal(PacketStream& ps)
	{
	}
}
