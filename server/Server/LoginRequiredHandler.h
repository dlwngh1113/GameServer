#pragma once
#include "CommandHandler.h"
#include "User.h"

class LoginRequiredHandler : public CommandHandler
{
protected:
	std::shared_ptr<User> m_user;

public:
	virtual void Handle() override final;
	virtual void HandleCommand() = 0;
};
