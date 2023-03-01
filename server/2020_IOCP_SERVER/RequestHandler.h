#pragma once
#include"BaseRequestHandler.h"

class User;

class RequestHandler : public BaseRequestHandler
{
protected:
	std::shared_ptr<User> m_user = nullptr;
public:
	void Handle() override final;
	virtual void HandleRequest() = 0;
	virtual BaseRequestHandler* Create() = 0;
};