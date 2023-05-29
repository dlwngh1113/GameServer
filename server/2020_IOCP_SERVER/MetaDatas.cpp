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
    std::unique_ptr<sql::ResultSet> result = DBWorker::LoadPlaces();

    if (result->rowsCount() > 0)
    {
        while (result->next())
        {
            int id = result->getInt("id");
            int width = result->getInt("width");
            int height = result->getInt("height");

            auto place = new Place(id, width, height, 8, 8);
            AddPlace(place);
        }
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
