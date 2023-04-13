#include "stdafx.h"
#include "MetaDatas.h"
#include "Logger.h"
#include "DBConnector.h"
#include "DBWorker.h"

MetaDatas* MetaDatas::s_instance = nullptr;

void MetaDatas::Initialize()
{
    Log("MetaDatas Load Started");
    LoadMetaDatas();
    Log("MetaDatas Load Finshed");
}

void MetaDatas::LoadMetaDatas()
{
    sql::ResultSet* result = DBWorker::LoadPlaces();

    if (result->rowsCount() > 0)
    {
        while (result->next())
        {
            int id = result->getInt(1);
            int width = result->getInt(2);
            int height = result->getInt(3);

            auto place = new Place(id, width, height, 8, 8);
            AddPlace(place);
        }
    }
    else
    {
        int id{ 0 };
        auto place = new Place(id, WORLD_WIDTH, WORLD_HEIGHT, 8, 8);
        m_places[id++] = place;
    }
}

void MetaDatas::AddPlace(Place* place)
{
    m_places.insert(std::make_pair(place->GetId(), place));
}

MetaDatas::~MetaDatas()
{
}

Place* MetaDatas::GetPlace(int id)
{
    auto value = m_places[id];

    return value;
}
