#include "stdafx.h"
#include "Place.h"

Place::Place()
{
	m_sectors.resize(WORLD_HEIGHT / SECTOR_SIZE);
	for (int y = 0; y < WORLD_HEIGHT / SECTOR_SIZE; ++y)
	{
		m_sectors[y].reserve(WORLD_WIDTH / SECTOR_SIZE);
		for (int x = 0; x < WORLD_WIDTH / SECTOR_SIZE; ++x)
		{
			m_sectors[y].emplace_back(x, y, SECTOR_SIZE, SECTOR_SIZE);
		}
	}
}

void Place::SetPosition(int x, int y)
{

}

std::vector<Sector> Place::GetInterestedSectors(int x, int y)
{
	
	return std::vector<Sector>();
}
