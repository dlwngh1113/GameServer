#pragma once
#include "EventBody.h"

namespace Common
{
	class COMMON_LIB_API TeleportEventBody : public EventBody
	{
	public:
		std::string userId;
		float x, y;

	public:
		explicit TeleportEventBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}