#include "pch.h"
#include "TeleportCommandBody.h"

namespace Common
{
	TeleportCommandBody::TeleportCommandBody()
		: CommandBody(Command::Teleport)
	{
	}

	TeleportCommandBody::~TeleportCommandBody()
	{
	}

	void TeleportCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y;
	}

	void TeleportCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y;
	}

	TeleportResponseBody::TeleportResponseBody()
		: ResponseBody(Command::Teleport)
	{
	}

	TeleportResponseBody::~TeleportResponseBody()
	{
	}

	void TeleportResponseBody::SerializeInternal(PacketStream& ps)
	{
	}

	void TeleportResponseBody::DeserializeInternal(PacketStream& ps)
	{
	}
}
