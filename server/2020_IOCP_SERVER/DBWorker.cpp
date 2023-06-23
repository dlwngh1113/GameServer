#include "stdafx.h"
#include "DBWorker.h"
#include "User.h"
#include "Place.h"
#include "Logger.h"
#include "ConnectionPool.h"

std::unique_ptr<sql::ResultSet> DBWorker::LoadMetaDatas()
{
	auto conn = ConnectionPool::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement>preparedStatement{ conn->prepareStatement("SELECT * FROM r_MetaDatas") };
	
	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	ConnectionPool::GetInstance().ReleaseConnection(conn);

	return result;
}

std::unique_ptr<sql::ResultSet> DBWorker::LoadPlaces()
{
	auto conn = ConnectionPool::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_LoadPlaces") };

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	ConnectionPool::GetInstance().ReleaseConnection(conn);

	return result;
}

std::unique_ptr<sql::ResultSet> DBWorker::GetOrCreateUser(char name[MAX_ID_LEN])
{
	auto conn = ConnectionPool::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_GetOrCreateUser(?)") };
	preparedStatement->setString(1, name);

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	ConnectionPool::GetInstance().ReleaseConnection(conn);

	return result;
}

void DBWorker::AddUser(char name[MAX_ID_LEN])
{
	auto conn = ConnectionPool::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_AddUser(?)") };
	preparedStatement->setString(1, name);

	preparedStatement->executeUpdate();

	ConnectionPool::GetInstance().ReleaseConnection(conn);
}

// name level x y exp hp placeId
void DBWorker::UpdateUser(std::shared_ptr<User> user)
{
	int nParamIndex = 0;
	auto conn = ConnectionPool::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_UpdateUser(?, ?, ?, ?, ?, ?, ?)") };

	preparedStatement->setString(++nParamIndex, user->GetName());
	preparedStatement->setInt(++nParamIndex, user->GetLevel());
	preparedStatement->setInt(++nParamIndex, user->GetX());
	preparedStatement->setInt(++nParamIndex, user->GetY());
	preparedStatement->setInt(++nParamIndex, user->GetExp());
	preparedStatement->setInt(++nParamIndex, user->GetHp());
	preparedStatement->setInt(++nParamIndex, user->GetPlace()->GetId());

	if (preparedStatement->executeUpdate())
		LogFormat("player [%s] DB update succeed!\n", user->GetName());
	else
		LogFormat("player [%s] DB update failed!\n", user->GetName());

	ConnectionPool::GetInstance().ReleaseConnection(conn);
}

std::unique_ptr<sql::ResultSet> DBWorker::GetUser(char name[MAX_ID_LEN])
{
	auto conn = ConnectionPool::GetInstance().GetConnection();
	std::unique_ptr<sql::PreparedStatement> preparedStatement{ conn->prepareStatement("CALL smo_GetUser(?)") };
	preparedStatement->setString(1, name);

	std::unique_ptr<sql::ResultSet> result{ preparedStatement->executeQuery() };

	ConnectionPool::GetInstance().ReleaseConnection(conn);

	return result;
}
