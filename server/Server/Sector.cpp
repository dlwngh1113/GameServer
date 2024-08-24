#include "stdafx.h"
#include "Sector.h"

Sector::Sector(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

bool Sector::IsInSector(int x, int y)
{
	if (x < m_x || x >= m_x)
		return false;
	if (y < m_y || y >= m_y)
		return false;

	return true;
}
