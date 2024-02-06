#include "stdafx.h"
#include "MetaDatas.h"
#include "Logger.h"

MetaDatas MetaDatas::s_instance;

void MetaDatas::Initialize()
{
    Log("MetaDatas Load Started");
    LoadMetaDatas();
    Log("MetaDatas Load Finshed");
}

void MetaDatas::LoadMetaDatas()
{
}

MetaDatas::~MetaDatas()
{
}
