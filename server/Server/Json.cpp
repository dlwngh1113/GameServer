#include "stdafx.h"
#include "Json.h"

Json::Json(const char* fileName)
{
	ifstream in(fileName, ios::binary);
	if (!in)
	{
		cerr << "[Error]" << fileName << endl;
	}
}
