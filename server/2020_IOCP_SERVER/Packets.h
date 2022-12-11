#pragma once
#include"BasePacket.h"

constexpr int WORLD_WIDTH = 800;
constexpr int WORLD_HEIGHT = 800;
constexpr int MAX_STR_LEN = 100;
constexpr int MAX_ID_LEN = 10;
constexpr int MAX_USER = 10000;
constexpr int SERVER_PORT = 3500;

constexpr char MV_UP = 0;
constexpr char MV_DOWN = 1;
constexpr char MV_LEFT = 2;
constexpr char MV_RIGHT = 3;

constexpr char SC_PACKET_LOGIN_OK = 0;
constexpr char SC_PACKET_MOVE = 1;
constexpr char SC_PACKET_ENTER = 2;
constexpr char SC_PACKET_EXIT = 3;
constexpr char SC_PACKET_CHAT = 4;
constexpr char SC_PACKET_LOGIN_FAIL = 5;
constexpr char SC_PACKET_STAT_CHANGE = 6;

constexpr char CS_LOGIN = 0;
constexpr char CS_MOVE = 1;
constexpr char CS_ATTACK = 2;
constexpr char CS_CHAT = 3;
constexpr char CS_LOGOUT = 4;
constexpr char CS_TELEPORT = 5;				// ���� �׽�Ʈ�� ���� �׽�Ʈ�� ���� �ڷ���Ʈ�� Hot Spot �ؼ�

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