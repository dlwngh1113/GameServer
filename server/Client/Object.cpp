#include "pch.h"
#include "Object.h"

namespace ClientFramework
{
	Object::Object()
		: m_rect()
	{
	}

	void Object::Move(float dx, float dy)
	{
		m_rect.x += dx;
		m_rect.y += dy;
	}

	void Object::Teleport(float x, float y)
	{
		m_rect.x = x;
		m_rect.y = y;
	}

	void Object::SetSize(float w, float h)
	{
		m_rect.w = w;
		m_rect.h = h;
	}
}
