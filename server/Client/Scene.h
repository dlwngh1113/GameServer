#pragma once
#include "Object.h"
#include "Player.h"
#include "Camera.h"

namespace ClientFramework
{
	class Window;
	class Label;

	class Scene
	{
	protected:
		Player* m_player;
		std::vector<std::unique_ptr<Object>> m_objects;
		Window* m_window;
		Label* m_label;
		std::unique_ptr<Camera> m_worldCamera;
		SDL_Point m_windowSize;

	public:
		Scene();

	public:
		virtual void Initialize(const SDL_Point& windowSize);
		virtual void Render();
		virtual void UpdateFrame();

		void SetPlayer(std::unique_ptr<Player> player);
		void AddObject(std::unique_ptr<Object> object);

		void OnWindowSizeChanged(int width, int height);

		Label* GetLabel() { return m_label; }

		// Static member functions
	public:
		static Scene* currentScene();
	};
}
