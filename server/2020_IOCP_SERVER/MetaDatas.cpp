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
    //DBConnector* dbc = DBWorker::LoadMetaDatas();

    //if (dbc)
    //{
    //    do 
    //    {
    //        int id, width, height;
    //        SQLLEN cId, cWidth, cHeight;

    //        SQLBindCol(dbc->GetStatement(), 1, SQL_C_LONG, &id, sizeof(id), &cId);
    //        SQLBindCol(dbc->GetStatement(), 2, SQL_C_LONG, &width, sizeof(width), &cWidth);
    //        SQLBindCol(dbc->GetStatement(), 3, SQL_C_LONG, &height, sizeof(height), &cHeight);

    //        auto place = new Place(id, width, height, 8, 8);
    //    } while (SQLFetch(dbc->GetStatement()));
    //}
    //else
    {
        int id{ 0 };
        auto place = new Place(id, ClientCommon::WORLD_WIDTH, ClientCommon::WORLD_HEIGHT, 8, 8);
        m_places[id++] = place;
    }
}

MetaDatas::~MetaDatas()
{
}

Place* MetaDatas::GetPlace(int id)
{
    auto value = m_places[id];

    return value;
}
