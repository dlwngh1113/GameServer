#pragma once

class DBUtil
{
public:
	static std::shared_ptr<sql::ResultSet> GetUser(const std::string& id, const std::string& password);
};
