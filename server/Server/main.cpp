#include "stdafx.h"
#include "CServer.h"

int main(int argc, char* argv[])
{
	CServer::instance().Run();
	return 0;
}