#pragma once
#include "Scene.h"

namespace ClientFramework
{
	class Framework
	{
	protected:
		SDL_Window* m_window;

		// Current scene
		unique_ptr<Scene> m_scene;

		// EventType, Callback
		unordered_map<Uint32, function<void(const SDL_Event&)>> m_events;

	public:
		Framework();

	public:
		Scene* scene() { return m_scene.get(); }

	public:
		void Initialize();
		void Run();
		void Release();

		bool LoadScene(unique_ptr<Scene> scene);

	private:
		void InitializeSDL();
		void InitializeEvents();

		// Static Member Variables
	private:
		static Framework s_instance;

		// Static Member Functions
	public:
		static Framework& instance() { return s_instance; }
	};
}
