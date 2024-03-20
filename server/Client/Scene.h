#pragma once
#include "Object.h"
#include "Player.h"
#include "UIBase.h"

namespace ClientFramework
{
	class Scene
	{
	protected:
		unique_ptr<Player> m_player;
		vector<unique_ptr<Object>> m_objects;
		unique_ptr<UIBase> m_window;

	public:
		Scene();

	public:
		virtual void Initialize();
		virtual void Render();
		virtual void UpdateFrame();

		void AddObject(unique_ptr<Object> object);
	};
}
