#pragma once
class IFactory
{
public:
	IFactory();
	virtual ~IFactory();
	virtual void Init() = 0;
};

