#include "stdafx.h"
#include "DBWorker.h"
#include "DBConnector.h"

sql::ResultSet* DBWorker::LoadMetaDatas()
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement>preparedStatement{ conn->prepareStatement("SELECT * FROM r_MetaDatas") };
	
	sql::ResultSet* result = preparedStatement->executeQuery();

	return result;
}

sql::ResultSet* DBWorker::LoadPlaces()
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_LoadPlaces") };

	sql::ResultSet* result = preparedStatement->executeQuery();

	return result;
}

void DBWorker::AddUser(char name[MAX_ID_LEN])
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_AddUser(:name)") };
	preparedStatement->setQueryAttrString(":name", name);

	preparedStatement->executeQuery();
}

void DBWorker::UpdateUser(std::shared_ptr<User> user)
{
}

sql::ResultSet* DBWorker::GetUser(char name[MAX_ID_LEN])
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_GetUser(:name)") };
	preparedStatement->setQueryAttrString(":name", name);

	sql::ResultSet* result = preparedStatement->executeQuery();

	return result;
}
