#pragma once
#include"User.h"
#include"BaseServer.h"

class CServer : public BaseServer
{
protected:
public:
	CServer();
	virtual ~CServer();

	void Run() override;
};