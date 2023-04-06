#include "stdafx.h"
#include "MetaDatas.h"
#include "Logger.h"
#include"DBWorker.h"

MetaDatas* MetaDatas::s_instance = nullptr;

void MetaDatas::Initialize()
{
    Log("MetaDatas Load Started");
    LoadMetaDatas();
    Log("MetaDatas Load Finshed");
}

void MetaDatas::LoadMetaDatas()
{
    int id{ 0 };
    auto place = new Place(id, ClientCommon::WORLD_WIDTH, ClientCommon::WORLD_HEIGHT, 8, 8);
    m_places[id++] = place;
}

MetaDatas::~MetaDatas()
{
}

Place* MetaDatas::GetPlace(int id)
{
    auto value = m_places[id];

    return value;
}
