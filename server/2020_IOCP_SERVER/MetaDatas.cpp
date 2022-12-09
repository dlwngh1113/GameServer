#include "stdafx.h"
#include "MetaDatas.h"

MetaDatas* MetaDatas::s_instance = nullptr;

void MetaDatas::Init()
{
    Logger::Info("MetaDatas Load Started");
    int id{ 0 };
    auto place = new Place(WORLD_WIDTH, WORLD_HEIGHT, 8, 8);
    m_places[id++] = place;
    Logger::Info("MetaDatas Load Finshed");
}

Place* MetaDatas::GetPlace(int id)
{
    auto value = m_places[id];

    return value;
}
