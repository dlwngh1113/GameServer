#pragma once

class Handler
{
public:
	Handler();
	virtual ~Handler();

protected:
	virtual void Handle() = 0;
};

