#pragma once
#include<rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

class Guid
{
private:
	TCHAR guid[129];
public:
	TCHAR* data() const;
	TCHAR*& data();
	static Guid NewGuid();
};

