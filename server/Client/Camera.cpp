#include "pch.h"
#include "Camera.h"

namespace ClientFramework
{
	Camera::Camera()
		: m_offset{}
		, m_pos{}
		, m_target(nullptr)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::SetOffset(int x, int y)
	{
		m_offset.x = x;
		m_offset.y = y;
	}

	void Camera::UpdateFrame()
	{
		if (m_target)
		{
			m_pos.x = m_offset.x - m_target->pos().x;
			m_pos.y = m_offset.y - m_target->pos().y;
		}
	}
}
