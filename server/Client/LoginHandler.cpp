#include "pch.h"
#include "LoginHandler.h"

LoginHandler::LoginHandler()
{
}

LoginHandler::~LoginHandler()
{
}

void LoginHandler::Handle()
{
}

Handler* LoginHandler::Create()
{
	return new LoginHandler;
}
