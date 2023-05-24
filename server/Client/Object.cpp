#include "pch.h"
#include "Object.h"

Object::Object()
{
}

Object::Object(int nX, int nY, int nWidth, int nHeight) : m_position{ nX, nY, nWidth, nHeight }
{
}

Object::~Object()
{
}
