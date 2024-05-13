#pragma once
#include "EventBody.h"

namespace Common
{
	class COMMON_LIB_API ChattingEventBody : public EventBody
	{
	public:
		std::string message;
		explicit ChattingEventBody();

	protected:
		virtual void SerializeInternal(PacketStream& ps) override;
		virtual void DeserializeInternal(PacketStream& ps) override;
	};
}
