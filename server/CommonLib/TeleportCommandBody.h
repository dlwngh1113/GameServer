#pragma once
#include "CommandBody.h"
#include "ResponseBody.h"

namespace Common
{
	class COMMON_LIB_API TeleportCommandBody : public CommandBody
	{
	public:
		float x, y;

	public:
		explicit TeleportCommandBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};

	class COMMON_LIB_API TeleportResponseBody : public ResponseBody
	{
	public:
		explicit TeleportResponseBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}