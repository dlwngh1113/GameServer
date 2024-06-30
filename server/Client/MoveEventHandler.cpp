#include "pch.h"
#include "MoveEventHandler.h"

void MoveEventHandler::Handle()
{
	Common::MoveEventBody body;
	Common::PacketStream ps;
	body.Deserialize(ps);
}
