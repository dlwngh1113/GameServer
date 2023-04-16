#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>

#include "Resource.h"