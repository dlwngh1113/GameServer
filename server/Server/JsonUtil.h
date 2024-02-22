#pragma once

class JsonUtil
{
public:
	boost::json::value Parse(const char* fileName);
	void Test();

	// Static member variables
private:
	static JsonUtil s_instance;

	// Static member functions
public:
	static JsonUtil& instance() { return s_instance; }
};
