#pragma once

//
constexpr int WORLD_WIDTH = 800;
constexpr int WORLD_HEIGHT = 800;

constexpr int MAX_STR_LEN = 100;
constexpr int MAX_ID_LEN = 10;

// 서버 세팅
constexpr int MAX_USER = 10000;
constexpr int SERVER_PORT = 3500;
constexpr int  KEY_SERVER = 1000000;

constexpr int NUM_NPC = 10'000;
constexpr int MAX_THREAD_COUNT = 6;

// IO 세팅
constexpr char OP_MODE_RECV = 0;
constexpr char OP_MODE_SEND = 1;
constexpr char OP_MODE_ACCEPT = 2;

constexpr int MAX_BUFFER = 4096;
constexpr int MIN_BUFFER = 1024;

//
constexpr char MV_UP = 0;
constexpr char MV_DOWN = 1;
constexpr char MV_LEFT = 2;
constexpr char MV_RIGHT = 3;

// 서버 to 클라이언트 명령
constexpr char SC_PACKET_LOGIN_OK = 0;
constexpr char SC_PACKET_MOVE = 1;
constexpr char SC_PACKET_ENTER = 2;
constexpr char SC_PACKET_EXIT = 3;
constexpr char SC_PACKET_CHAT = 4;
constexpr char SC_PACKET_LOGIN_FAIL = 5;
constexpr char SC_PACKET_STAT_CHANGE = 6;

// 클라이언트 to 서버 명령
constexpr char CS_LOGIN = 0;
constexpr char CS_MOVE = 1;
constexpr char CS_ATTACK = 2;
constexpr char CS_CHAT = 3;
constexpr char CS_LOGOUT = 4;
constexpr char CS_TELEPORT = 5;				// 부하 테스트용 동접 테스트를 위해 텔러포트로 Hot Spot 해소