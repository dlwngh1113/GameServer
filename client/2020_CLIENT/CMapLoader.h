#pragma once
#include"stdafx.h"

class CMapLoader
{
public:
	static void LoadMap(short map[ClientCommon::WORLD_WIDTH][ClientCommon::WORLD_HEIGHT], const char* fileName);
	static void SaveMap(short map[ClientCommon::WORLD_WIDTH][ClientCommon::WORLD_HEIGHT], const char* fileName);
};

