#pragma once
#include"BasePacket.h"
#include"Defines.h"

#pragma pack(push, 1)

// 채팅

struct ChattingRequest : BasePacket
{
	char  message[MAX_STR_LEN];
};

struct ChattingEvent : BasePacket
{
	int	  id;
	char  message[MAX_STR_LEN];
};

// 상태 변경

struct StatusChangedEvent : BasePacket
{
	int  id;
	short hp;
	short level;
	int   exp;
	char message[MAX_STR_LEN];
};

// 이동


// 장소

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

// 공격

struct AttackRequest : BasePacket
{
	int atkTime;
};

#pragma pack(pop)