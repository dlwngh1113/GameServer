#pragma once
#include "Sector.h"

struct SectorChangeInfo
{
	std::unordered_set<Sector*> exitedSectors;
	std::unordered_set<Sector*> enteredSectors;
	std::unordered_set<Sector*> notChangedSectors;
};

