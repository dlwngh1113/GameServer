#pragma once

class Handler
{
public:
	Handler();
	virtual ~Handler();

public:
	virtual void Handle() = 0;
};

