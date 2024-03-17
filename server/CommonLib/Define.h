#pragma once

#ifdef _WIN32
#ifdef COMMON_LIB_EXPORTS
#define COMMON_LIB_API __declspec(dllexport)
#else
#define COMMON_LIB_API __declspec(dllimport)
#endif
#else
#define COMMON_LIB_API
#endif