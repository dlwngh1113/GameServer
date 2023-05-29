#include "stdafx.h"
#include "DBWorker.h"
#include "DBConnector.h"

std::unique_ptr<sql::ResultSet> DBWorker::LoadMetaDatas()
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement>preparedStatement{ conn->prepareStatement("SELECT * FROM r_MetaDatas") };
	
	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };
	DBConnector::GetInstance()->AddConnection(conn);

	return result;
}

std::unique_ptr<sql::ResultSet> DBWorker::LoadPlaces()
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_LoadPlaces") };

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };
	DBConnector::GetInstance()->AddConnection(conn);

	return result;
}

void DBWorker::AddUser(char name[MAX_ID_LEN])
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_AddUser(?)") };
	preparedStatement->setString(1, name);

	preparedStatement->executeQuery();
	DBConnector::GetInstance()->AddConnection(conn);
}

void DBWorker::UpdateUser(std::shared_ptr<User> user)
{
}

std::unique_ptr<sql::ResultSet> DBWorker::GetUser(char name[MAX_ID_LEN])
{
	sql::Connection* conn = DBConnector::GetInstance()->GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_GetUser(?)") };
	preparedStatement->setString(1, name);

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };
	DBConnector::GetInstance()->AddConnection(conn);

	return result->next() ? nullptr : std::move(result);
}
