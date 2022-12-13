#pragma once
#include "RequestHandler.h"

#pragma region PacketData

#pragma pack(push, 1)
struct SPlace
{

};

struct PlaceEnterRequest : BasePacket
{
	int placeId;
	SPlace placeInfo;
};
#pragma pack(pop)

#pragma endregion


class PlaceEnterRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	BaseRequestHandler* Create() override;
};

