#include "pch.h"
#include "UIBase.h"
#include "Key.h"

namespace ClientFramework
{
	UIBase::UIBase()
		: m_parent(nullptr)
	{
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		for (std::unique_ptr<UIBase>& child : m_children)
		{
			child->Initialize();
		}
	}

	void UIBase::Render()
	{
		for (std::unique_ptr<UIBase>& child : m_children)
		{
			child->Render();
		}
	}

	void UIBase::UpdateFrame()
	{
		for (std::unique_ptr<UIBase>& child : m_children)
		{
			child->UpdateFrame();
		}
	}

	void UIBase::ScrollWheel(const SDL_MouseWheelEvent& evt)
	{
	}

	void UIBase::MouseClick(const SDL_MouseButtonEvent& evt)
	{
		SDL_Point mousePosition{ evt.x, evt.y };

		if (!SDL_PointInRect(&mousePosition, &m_rect))
			return;
	}

	void UIBase::MouseMove(const SDL_MouseMotionEvent& evt)
	{
		SDL_Point mousePosition{ evt.x, evt.y };

		if (!SDL_PointInRect(&mousePosition, &m_rect))
			return;

		//
		//
		//

		OnMouseHover();
		OnMouseMove(mousePosition.x, mousePosition.y);

		//
		//
		//

		for (auto& child : m_children)
			child->MouseMove(evt);
	}

	void UIBase::OnMouseButtonDown()
	{
	}

	void UIBase::OnMouseButtonUp()
	{
	}

	void UIBase::OnMouseHover()
	{
	}

	void UIBase::OnMouseMove(Sint32 x, Sint32 y)
	{
	}

	void UIBase::SetParentPosition(int x, int y)
	{
		m_rect.x = x;
		m_rect.y = y;
	}

	void UIBase::SetSize(int width, int height)
	{
		m_rect.w = width;
		m_rect.h = height;
	}
}
