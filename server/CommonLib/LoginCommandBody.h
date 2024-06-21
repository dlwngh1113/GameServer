#pragma once
#include "CommandBody.h"
#include "ResponseBody.h"

namespace Common
{
	class COMMON_LIB_API LoginCommandBody : public CommandBody
	{
	public:
		std::string userId;
		std::string password;

	public:
		LoginCommandBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};

	class COMMON_LIB_API LoginResponseBody : public ResponseBody
	{
	public:
		float x, y;

	public:
		LoginResponseBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
