#include "pch.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::SetPosition(int nX, int nY, int nWidth, int nHeight)
{
	m_position = { nX, nY, nWidth, nHeight };
}
