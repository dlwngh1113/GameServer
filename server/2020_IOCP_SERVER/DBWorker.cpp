#include "stdafx.h"
#include "DBWorker.h"

void DBWorker::GetUser(char* name)
{
	DBConnector dbConnector;
	
	SQLWCHAR* statement = dbConnector.ConvertToMultibyteQuery("EXEC GetUser (?)");
	
	dbConnector.ExecuteDirectSQL(statement);
	dbConnector.AddParameter(name);
}
