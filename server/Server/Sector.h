#pragma once
#include "User.h"

class Sector
{
	int m_x, m_y;
	int m_width, m_height;

public:
	explicit Sector(int x, int y, int width, int height);

public:
	bool IsInSector(int x, int y);
};
