#pragma once
#include "Scene.h"
#include "Singleton.h"

namespace ClientFramework
{
	class Framework : public Singleton<Framework>
	{
	protected:
		SDL_Window* m_window;
		SDL_Point m_windowSize;

		// Current scene
		std::unique_ptr<Scene> m_scene;

		// EventType, Callback
		std::unordered_map<Uint32, std::function<void(const SDL_Event&)>> m_events;

	public:
		Framework();

	public:
		Scene* scene() { return m_scene.get(); }

	public:
		void Initialize();
		void Run();
		void Release();

		bool LoadScene(std::unique_ptr<Scene> scene);

	private:
		void InitializeSDL();
		void InitializeEvents();
	};
}
