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
#include <stdexcept>

// STL
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// boost
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/array.hpp>
#include <boost/thread/sync_queue.hpp>

// mysql
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

#ifdef _WIN32
	#pragma comment(lib, "lua54.lib")
	#pragma comment(lib, "mysqlcppconn.lib")
	#pragma comment(lib, "CommonLib.lib")
	#pragma comment(lib, "libboost_thread-vc143-mt-x64-1_86.lib")
	#pragma comment(lib, "libboost_chrono-vc143-mt-x64-1_86.lib")
#endif // _WIN32

#include "../Common/Common.hpp"
#include "../CommonLib/Packets.h"
#include "../CommonLib/RingBuffer.h"