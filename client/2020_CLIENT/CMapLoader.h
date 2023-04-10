#pragma once
#include"stdafx.h"

class CMapLoader
{
public:
	static void LoadMap(short map[WORLD_WIDTH][WORLD_HEIGHT], const char* fileName);
	static void SaveMap(short map[WORLD_WIDTH][WORLD_HEIGHT], const char* fileName);
};

