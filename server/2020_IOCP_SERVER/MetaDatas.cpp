#include "stdafx.h"
#include "MetaDatas.h"
#include "Logger.h"

MetaDatas* MetaDatas::s_instance = nullptr;

void MetaDatas::Init()
{
    Log("MetaDatas Load Started");
    int id{ 0 };
    auto place = new Place(id, ClientCommon::WORLD_WIDTH, ClientCommon::WORLD_HEIGHT, 8, 8);
    m_places[id++] = place;
    Log("MetaDatas Load Finshed");
}

Place* MetaDatas::GetPlace(int id)
{
    auto value = m_places[id];

    return value;
}
