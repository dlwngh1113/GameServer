#include "pch.h"
#include "MovableObject.h"

MovableObject::MovableObject() : Object()
{
}

MovableObject::MovableObject(int nX, int nY, int nWidth, int nHeight) : Object{ nX, nY, nWidth, nHeight }
{
}

MovableObject::~MovableObject()
{
}
