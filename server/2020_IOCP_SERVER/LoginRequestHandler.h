#pragma once
#include "RequestHandler.h"

#pragma region PacketData

#pragma pack(push, 1)
#pragma pack(pop)

#pragma endregion

class LoginRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	BaseRequestHandler* Create() override;
};