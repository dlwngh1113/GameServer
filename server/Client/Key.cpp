#include "pch.h"
#include "Key.h"

namespace ClientFramework
{
	Key Key::s_instance;

	void Key::OnKeyDown(const SDL_Keycode& code)
	{
		m_keyState[code] = SDL_KEYDOWN;
	}

	void Key::OnKeyUp(const SDL_Keycode& code)
	{
		m_keyState[code] = SDL_KEYUP;
	}

	bool Key::IsKeyDown(const SDL_Keycode& code)
	{
		auto iter = m_keyState.find(code);
		if (iter != m_keyState.end())
		{
			return iter->second == SDL_KEYDOWN;
		}
		return false;
	}

	bool Key::IsKeyUp(const SDL_Keycode& code)
	{
		auto iter = m_keyState.find(code);
		if (iter != m_keyState.end())
		{
			return iter->second == SDL_KEYUP;
		}

		return false;
	}

	void Key::OnMouseButton(const SDL_MouseButtonEvent& evt)
	{
		m_mouseState[evt.button] = evt.state;
	}

	void Key::OnMouseMotion(const SDL_MouseMotionEvent& evt)
	{
		m_mousePosition.x = evt.x;
		m_mousePosition.y = evt.y;
	}

	void Key::OnMouseWheel(const SDL_MouseWheelEvent& evt)
	{
		m_mouseWheel.x = evt.preciseX;
		m_mouseWheel.y = evt.preciseY;
	}

	bool Key::IsMouseButtonDown(const Uint8& button)
	{
		auto iter = m_mouseState.find(button);
		if (iter != m_mouseState.end())
		{
			return iter->second == SDL_MOUSEBUTTONDOWN;
		}

		return false;
	}

	bool Key::IsMouseButtonUp(const Uint8& button)
	{
		auto iter = m_mouseState.find(button);
		if (iter != m_mouseState.end())
		{
			return iter->second == SDL_MOUSEBUTTONUP;
		}

		return false;
	}
}