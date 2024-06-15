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

// boost
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/array.hpp>

// mysql
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

#pragma comment(lib, "lua54.lib")
#pragma comment(lib, "mysqlcppconn.lib")
#pragma comment(lib, "CommonLib.lib")

#include "../Common/Common.hpp"
#include "../CommonLib/Packets.h"