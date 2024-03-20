// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "Framework.h"

int SDL_main(int argc, char* argv[])
{
	ClientFramework::Framework::instance().Initialize();
	ClientFramework::Framework::instance().Run();

	return 0;
}