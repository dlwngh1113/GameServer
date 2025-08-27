#include "pch.h"
#include "LoginCommandBody.h"

namespace Common
{
	LoginCommandBody::LoginCommandBody()
		: CommandBody(Command::Login)
	{
	}

	void LoginCommandBody::SerializeInternal(PacketStream& ps)
	{
		ps << userId << password;
	}

	void LoginCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> userId >> password;
	}

	LoginResponseBody::LoginResponseBody()
		: ResponseBody(Command::Login)
		, x(0), y(0)
	{
	}

	void LoginResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps << x << y;
	}

	void LoginResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps >> x >> y;
	}
}