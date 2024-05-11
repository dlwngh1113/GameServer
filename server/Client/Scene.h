#pragma once
#include "Object.h"
#include "Player.h"
#include "UIBase.h"

namespace ClientFramework
{
	class Scene
	{
	protected:
		std::unique_ptr<Player> m_player;
		std::vector<std::unique_ptr<Object>> m_objects;
		std::unique_ptr<UIBase> m_window;

	public:
		Scene();

	public:
		virtual void Initialize();
		virtual void Render();
		virtual void UpdateFrame();

		void AddObject(std::unique_ptr<Object> object);

		void OnWindowSizeChanged(int width, int height);

		// Static member functions
	public:
		static Scene* currentScene();
	};
}
