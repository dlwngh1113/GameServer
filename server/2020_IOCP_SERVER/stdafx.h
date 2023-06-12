#pragma once

extern "C" {
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}

// C++
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <fstream>
#include <concurrent_queue.h>

// STL
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// windows
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <windows.h>
#include <WinSock2.h>
#include <ws2def.h>

// sql
#include <sqlext.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "MSWSock.lib")
#pragma comment(lib, "lua54.lib")
#pragma comment(lib, "mysqlcppconn.lib")

#include "../Common/Common.hpp"

struct OVER_EX {
	WSAOVERLAPPED wsa_over;
	char	op_mode;
	WSABUF	wsa_buf;
	unsigned char iocp_buf[MAX_BUFFER];
	int		object_id;
};