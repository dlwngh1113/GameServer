#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define OP_RECV 0
#define OP_SEND 1
#define OP_ACCEPT 2

#define BUF_SIZE 1024
#define MAX_BUFFER 4096
#define MIN_BUFFER BUF_SIZE
#define SERVER_PORT 9000
#define KEY_SERVER 12431
#define MAX_THREAD_COUNT 6