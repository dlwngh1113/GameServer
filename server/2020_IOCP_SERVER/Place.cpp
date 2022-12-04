#include "stdafx.h"
#include "Place.h"

Place::Place()
{
}

Place::~Place()
{
	for (int i = 0; i < nWidth; ++i)
		delete[] m_sectors[i];

	delete[] m_sectors;
}
