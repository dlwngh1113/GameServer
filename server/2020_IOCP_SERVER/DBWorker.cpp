#include "stdafx.h"
#include "DBWorker.h"
#include "DBConnector.h"
#include "User.h"
#include "Place.h"
#include "Logger.h"

std::unique_ptr<sql::ResultSet> DBWorker::LoadMetaDatas()
{
	auto conn = DBConnector::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement>preparedStatement{ conn->prepareStatement("SELECT * FROM r_MetaDatas") };
	
	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	return result;
}

std::unique_ptr<sql::ResultSet> DBWorker::LoadPlaces()
{
	auto conn = DBConnector::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_LoadPlaces") };

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	return result;
}

void DBWorker::AddUser(char name[MAX_ID_LEN])
{
	auto conn = DBConnector::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_AddUser(?)") };
	preparedStatement->setString(1, name);

	preparedStatement->executeUpdate();
}

// name level x y exp hp placeId
void DBWorker::UpdateUser(std::shared_ptr<User> user)
{
	int nParamIndex = 0;
	auto conn = DBConnector::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_UpdateUser(?, ?, ?, ?, ?, ?, ?)") };

	preparedStatement->setString(++nParamIndex, user->GetName());
	preparedStatement->setInt(++nParamIndex, user->GetLevel());
	preparedStatement->setInt(++nParamIndex, user->GetX());
	preparedStatement->setInt(++nParamIndex, user->GetY());
	preparedStatement->setInt(++nParamIndex, user->GetExp());
	preparedStatement->setInt(++nParamIndex, user->GetHp());
	preparedStatement->setInt(++nParamIndex, user->GetPlace()->GetId());

	if (preparedStatement->executeUpdate())
		LogFormat("player name [%s] DB update succeed!\n", user->GetName());
	else
		LogFormat("player name [%s] DB update failed!\n", user->GetName());
}

std::unique_ptr<sql::ResultSet> DBWorker::GetUser(char name[MAX_ID_LEN])
{
	auto conn = DBConnector::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_GetUser(?)") };
	preparedStatement->setString(1, name);

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	return result;
}
