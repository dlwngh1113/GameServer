#include "CMapLoader.h"

void CMapLoader::LoadMap(short map[ClientCommon::WORLD_WIDTH][ClientCommon::WORLD_HEIGHT], const char* fileName)
{
	std::ifstream in(fileName);
	int w, h;

	in >> w >> h;
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			in >> map[i][j];
		}
	}
}

void CMapLoader::SaveMap(short map[ClientCommon::WORLD_WIDTH][ClientCommon::WORLD_HEIGHT], const char* fileName)
{
	std::ofstream out(fileName);

	out << ClientCommon::WORLD_HEIGHT << ' ' << ClientCommon::WORLD_WIDTH << '\n';

	for (int i = 0; i < ClientCommon::WORLD_WIDTH; ++i)
	{
		for (int j = 0; j < ClientCommon::WORLD_HEIGHT; ++j)
		{
			out << map[i][j] << ' ';
		}
		out << '\n';
	}

	out.close();
}
