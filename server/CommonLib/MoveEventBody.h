#pragma once
#include "EventBody.h"

namespace Common
{
	class COMMON_LIB_API MoveEventBody : public EventBody
	{
	public:
		std::string userId;
		float x, y;
		int32_t moveTime;

	public:
		explicit MoveEventBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}