#pragma once
#include <string>

using namespace std;

//
constexpr int MAX_STR_LEN = 100;
constexpr int MAX_ID_LEN = 10;

// 서버 세팅
constexpr int MAX_USER = 10000;
constexpr int SERVER_PORT = 3500;

constexpr int NUM_NPC = 10'000;
constexpr int MAX_THREAD_COUNT = 6;

// IO 세팅
constexpr int MAX_BUFFER = 4096;
constexpr int MIN_BUFFER = 1024;