#pragma once
#include"Packets.h"
#include"RequestHandler.h"

#pragma region PacketData

#pragma pack(push, 1)
struct TeleportRequest : BasePacket
{
	short x, y;
};

struct TeleportResponse : BasePacket
{
};
#pragma pack(pop)

#pragma endregion


class TeleportRequestHandler : public RequestHandler
{
public:
	virtual void HandleRequest();
	virtual BaseRequestHandler* Create();
};