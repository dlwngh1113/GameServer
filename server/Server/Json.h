#pragma once

class Json
{
private:
	boost::json::value m_value;

public:
	Json(const char* fileName);
};
