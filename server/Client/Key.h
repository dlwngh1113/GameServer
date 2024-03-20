#pragma once

namespace ClientFramework
{
	class Key
	{
	private:
		// keycode, state
		unordered_map<SDL_Keycode, Uint32> m_keyState;

		// button, state
		unordered_map<Uint8, Uint32> m_mouseState;

		// Mouse x, y
		SDL_Point m_mousePosition;

		// Mouse wheel values (x: horizontal, y: vertical)
		SDL_FPoint m_mouseWheel;

	public:
		// It called when key pressed
		void OnKeyDown(const SDL_Keycode& code);

		// It called when key release
		void OnKeyUp(const SDL_Keycode& code);

		// Return true if given code key is pressed
		bool IsKeyDown(const SDL_Keycode& code);

		// Return true if given code key is released
		bool IsKeyUp(const SDL_Keycode& code);

		// It called when mouse click
		void OnMouseButton(const SDL_MouseButtonEvent& evt);

		// It called when mouse move
		void OnMouseMotion(const SDL_MouseMotionEvent& evt);

		// It called when mouse wheel
		void OnMouseWheel(const SDL_MouseWheelEvent& evt);

		// Return true if given mouse button is down
		bool IsMouseButtonDown(const Uint8& button);

		// Return true if given mouse button is up
		bool IsMouseButtonUp(const Uint8& button);

		// Static Member Variables
	private:
		static Key s_instance;

		// Static Member Funtions
	public:
		static Key& instance() { return s_instance; }
	};
}
