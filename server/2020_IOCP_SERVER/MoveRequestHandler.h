#pragma once
#include"Packets.h"
#include"RequestHandler.h"

#pragma region PacketData

#pragma pack(push ,1)
struct MoveRequest : BasePacket
{
	char  direction;
	int	  move_time;
};

struct MoveResponse : BasePacket
{
	int id;
	short x, y;
	int move_time;
};

struct UserMoveEvent : BasePacket
{
	int id;
	short x, y;
};
#pragma pack(pop)

#pragma endregion

class MoveRequestHandler : public RequestHandler
{
public:
	virtual void HandleRequest()  override;
	virtual BaseRequestHandler* Create() override;
};