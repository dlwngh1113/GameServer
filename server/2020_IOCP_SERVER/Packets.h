#pragma once
#include"BasePacket.h"
#include"Defines.h"

#pragma pack(push, 1)

// �α���

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

struct LogoutRequest : BasePacket
{
};

// ä��

struct ChattingRequest : BasePacket
{
	char  message[MAX_STR_LEN];
};

struct ChattingEvent : BasePacket
{
	int	  id;
	char  message[MAX_STR_LEN];
};

// ���� ����

struct StatusChangedEvent : BasePacket
{
	int  id;
	short hp;
	short level;
	int   exp;
	char message[MAX_STR_LEN];
};

// �̵�

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

struct TeleportRequest : BasePacket
{
	short x, y;
};

struct TeleportResponse : BasePacket
{
};

// ���

struct UserEnterEvent : BasePacket
{
	int  id;
	char name[MAX_ID_LEN];
	short x, y;
};

struct UserExitEvent : BasePacket
{
	int  id;
};

// ����

struct AttackRequest : BasePacket
{
	int atkTime;
};

#pragma pack(pop)