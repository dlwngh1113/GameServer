#include "stdafx.h"
#include "DBWorker.h"
#include "User.h"

void DBWorker::GetUser(User* user, char name[MAX_ID_LEN])
{
	DBConnector dbc;
	
	SQLWCHAR* statement = dbc.ConvertToMultibyteQuery("EXEC GetUser (?)");
	
	dbc.AddParameter(name);
	dbc.ExecuteDirectSQL(statement);

	short level, hp, x, y;
	int exp;
	SQLLEN cLevel, cHp, cX, cY, cExp;

	SQLBindCol(dbc.GetStatement(), 2, SQL_C_SHORT, &level, sizeof(level), &cLevel);
	SQLBindCol(dbc.GetStatement(), 3, SQL_C_CHAR, &hp, sizeof(hp), &cHp);
	SQLBindCol(dbc.GetStatement(), 4, SQL_C_FLOAT, &x, sizeof(x), &cX);
	SQLBindCol(dbc.GetStatement(), 5, SQL_C_FLOAT, &y, sizeof(y), &cY);
	SQLBindCol(dbc.GetStatement(), 6, SQL_C_FLOAT, &exp, sizeof(exp), &cExp);

	user->SetInfo(name, level, exp, hp, x, y);
}
