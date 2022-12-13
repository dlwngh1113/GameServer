#include "stdafx.h"
#include "PlaceEnterRequestHandler.h"

void PlaceEnterRequestHandler::HandleRequest()
{

}

BaseRequestHandler* PlaceEnterRequestHandler::Create()
{
	return new PlaceEnterRequestHandler;
}
