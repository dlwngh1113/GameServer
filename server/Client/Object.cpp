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
	m_position.x = nX * TILE_SIZE;
	m_position.y = nY * TILE_SIZE;
	m_position.w = TILE_SIZE;
	m_position.h = TILE_SIZE;
}
