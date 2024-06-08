#pragma once
#include "Object.h"
#include "Player.h"

namespace ClientFramework
{
	class Window;
	class Label;

	class Scene
	{
	protected:
		std::unique_ptr<Player> m_player;
		std::vector<std::unique_ptr<Object>> m_objects;
		Window* m_window;
		Label* m_label;

	public:
		Scene();

	public:
		virtual void Initialize();
		virtual void Render();
		virtual void UpdateFrame();

		void AddObject(std::unique_ptr<Object> object);

		void OnWindowSizeChanged(int width, int height);

		Label* GetLabel() { return m_label; }

		// Static member functions
	public:
		static Scene* currentScene();
	};
}
