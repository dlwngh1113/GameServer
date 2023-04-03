#include"stdafx.h"
#include"CServer.h"

int main()
{
	CServer* server = CServer::GetInstance();
	server->Run();
}