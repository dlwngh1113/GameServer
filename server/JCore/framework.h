#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#define OP_RECV 0
#define OP_SEND 1

#define BUF_SIZE 1024
#define MAX_BUFFER 4096
#define MIN_BUFFER BUF_SIZE