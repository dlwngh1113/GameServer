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
		ps.Write(userId);
		ps.Write(password);
	}

	void LoginCommandBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(userId);
		ps.Read(password);
	}

	LoginResponseBody::LoginResponseBody()
		: ResponseBody(Command::Login)
		, x(0), y(0)
	{
	}

	void LoginResponseBody::SerializeInternal(PacketStream& ps)
	{
		ps.Write(x);
		ps.Write(y);
	}

	void LoginResponseBody::DeserializeInternal(PacketStream& ps)
	{
		ps.Read(x);
		ps.Read(y);
	}
}