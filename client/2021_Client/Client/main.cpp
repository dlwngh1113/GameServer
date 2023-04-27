// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "Framework.h"

Framework* framework;

int SDL_main(int argc, char* argv[])
{
	framework = new Framework();
	framework->Run();
	return 0;
}