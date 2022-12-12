#pragma once
#include "RequestHandler.h"

#pragma region PacketData

#pragma pack(push, 1)
struct LoginRequest : BasePacket
{
	char  name[MAX_ID_LEN];
};

struct LoginResponse : BasePacket
{
	int  id;
	short x, y;
	short hp;
	short level;
	int   exp;
};

struct LoginFailResponse : BasePacket
{
	int	  id;
	char  message[MAX_STR_LEN];
};
#pragma pack(pop)

#pragma endregion

class LoginRequestHandler : public RequestHandler
{
public:
	void HandleRequest() override;
	BaseRequestHandler* Create() override;
};