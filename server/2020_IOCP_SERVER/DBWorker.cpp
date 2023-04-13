#include "stdafx.h"
#include "DBWorker.h"
#include "DBConnector.h"

sql::ResultSet* DBWorker::LoadMetaDatas()
{
	sql::PreparedStatement* preparedStatement = DBConnector::GetInstance()->GetPreparedStatement("SELECT * FROM r_MetaDatas");
	
	return preparedStatement->executeQuery();
}

sql::ResultSet* DBWorker::LoadPlaces()
{
	sql::PreparedStatement* preparedStatement = DBConnector::GetInstance()->GetPreparedStatement("CALL smo_LoadPlaces");
	return preparedStatement->executeQuery();
}

void DBWorker::AddUser(char name[MAX_ID_LEN])
{
	sql::PreparedStatement* preparedStatement = DBConnector::GetInstance()->GetPreparedStatement("CALL smo_AddUser(:name)");
	preparedStatement->setQueryAttrString(":name", name);

	preparedStatement->executeQuery();
}

void DBWorker::UpdateUser(std::shared_ptr<User> user)
{
}

sql::ResultSet* DBWorker::GetUser(char name[MAX_ID_LEN])
{
	sql::PreparedStatement* preparedStatement = DBConnector::GetInstance()->GetPreparedStatement("CALL smo_GetUser(:name)");
	preparedStatement->setQueryAttrString(":name", name);

	return preparedStatement->executeQuery();
}
