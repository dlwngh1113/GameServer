#include "pch.h"
#include "Object.h"

namespace ClientFramework
{
	Object::Object()
		: m_rect()
	{
	}

	void Object::Move(int dx, int dy)
	{
		m_rect.x += dx;
		m_rect.y += dy;
	}

	void Object::Teleport(int x, int y)
	{
		m_rect.x = x;
		m_rect.y = y;
	}
}
