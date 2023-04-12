#pragma once

extern "C" {
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}

#include <iostream>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <chrono>
#include <string>
#include <windows.h>  
#include <sqlext.h>
#include <fstream>
#include <WinSock2.h>
#include <ws2def.h>
#include <unordered_set>
#include <concurrent_queue.h>
#include <stdarg.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "lua54.lib")
#pragma comment(lib, "ClientCommon.lib")
#pragma comment(lib, "mysqlcppconn.lib")

#include "Packets.h"

struct OVER_EX {
	WSAOVERLAPPED wsa_over;
	char	op_mode;
	WSABUF	wsa_buf;
	unsigned char iocp_buf[MAX_BUFFER];
	int		object_id;
};