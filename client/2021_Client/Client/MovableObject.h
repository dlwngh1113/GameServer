#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	MovableObject();
	virtual ~MovableObject();

	virtual void Update(float flElapsedTime) = 0;
	virtual void Render() = 0;

	virtual void Move(int nDx, int nDy) = 0;
};
