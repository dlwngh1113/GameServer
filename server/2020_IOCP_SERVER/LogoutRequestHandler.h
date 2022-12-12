#pragma once
#include"RequestHandler.h"

#pragma region PacketData

#pragma pack(push, 1)
struct LogoutRequest : BasePacket
{
};
#pragma pack(pop)

#pragma endregion


class LogoutRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	LogoutRequestHandler* Create() override;
};

