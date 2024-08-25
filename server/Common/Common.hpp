#pragma once
#include <string>

//
constexpr int MAX_STR_LEN = 100;
constexpr int MAX_ID_LEN = 10;
constexpr int WORLD_WIDTH = 800;
constexpr int WORLD_HEIGHT = 800;
constexpr int SECTOR_SIZE = 50;

// 서버 세팅
constexpr int MAX_USER = 10000;
constexpr int SERVER_PORT = 3500;

constexpr int NUM_NPC = 10'000;
constexpr int MAX_THREAD_COUNT = 6;

// IO 세팅
constexpr int MAX_BUFFER = 4096;
constexpr int MIN_BUFFER = 1024;