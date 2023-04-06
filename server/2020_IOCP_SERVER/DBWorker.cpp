#include "stdafx.h"
#include"DBConnector.h"
#include "DBWorker.h"
#include "User.h"

void DBWorker::LoadMetaDatas()
{
	DBConnector dbc{ "EXEC LoadMetaDatas" };
	dbc.ExecuteDirectSQL();
}

void DBWorker::AddUser(char name[ClientCommon::MAX_ID_LEN])
{
	// name, level, exp, hp, x, y
	DBConnector dbc{ "EXEC AddUser ?, ?, ?, ?, ?, ?" };

	dbc.PrepareStatement();

	dbc.AddParameter(name);
	dbc.AddParameter(1);
	dbc.AddParameter(0);
	dbc.AddParameter(50);
	dbc.AddParameter(0);
	dbc.AddParameter(0);

	dbc.ExecutePreparedStatement();
}

void DBWorker::GetUser(std::shared_ptr<User> user, char name[ClientCommon::MAX_ID_LEN])
{
	DBConnector dbc{ "EXEC GetUser ?" };
	
	dbc.PrepareStatement();
	dbc.AddParameter(name);
	dbc.ExecutePreparedStatement();

	short level, hp, x, y, placeId;
	int exp;
	SQLLEN cLevel, cHp, cX, cY, cExp, cYPlaceId;

	SQLBindCol(dbc.GetStatement(), 2, SQL_C_SHORT, &level, sizeof(level), &cLevel);
	SQLBindCol(dbc.GetStatement(), 3, SQL_C_LONG, &exp, sizeof(exp), &cExp);
	SQLBindCol(dbc.GetStatement(), 4, SQL_C_SHORT, &hp, sizeof(hp), &cHp);
	SQLBindCol(dbc.GetStatement(), 5, SQL_C_SHORT, &x, sizeof(x), &cX);
	SQLBindCol(dbc.GetStatement(), 6, SQL_C_SHORT, &y, sizeof(y), &cY);
	SQLBindCol(dbc.GetStatement(), 7, SQL_C_SHORT, &placeId, sizeof(placeId), &cYPlaceId);
	
	SQLRETURN retCode = SQLFetch(dbc.GetStatement());

	if (retCode == SQL_SUCCESS)
	{
		user->SetInfo(name, level, exp, hp, x, y);

		Log("login %s %d %d %d %d %d\n", user->GetName(), user->GetLevel(), user->GetExp(), user->GetHp(), user->GetX(), user->GetY());
	}
	else
	{
		AddUser(name);
		user->SetInfo(name, 1, 0, 50, 0, 0);
	}
}

void DBWorker::UpdateUser(std::shared_ptr<User> user)
{
	// name, level, exp, hp, x, y
	DBConnector dbc{ "EXEC UpdateUser ?, ?, ?, ?, ?, ?" };

	dbc.PrepareStatement();

	dbc.AddParameter(user->GetName());
	dbc.AddParameter(user->GetLevel());
	dbc.AddParameter(user->GetExp());
	dbc.AddParameter(user->GetHp());
	dbc.AddParameter(user->GetX());
	dbc.AddParameter(user->GetY());

	dbc.ExecutePreparedStatement();
	Log("logout %s %d %d %d %d %d\n", user->GetName(), user->GetLevel(), user->GetExp(), user->GetHp(), user->GetX(), user->GetY());
}
