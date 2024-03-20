#include "pch.h"
#include "Framework.h"
#include "Renderer.h"
#include "Key.h"
#include "Time.h"
#include "Resource.h"

namespace ClientFramework
{
	Framework Framework::s_instance;

	Framework::Framework()
		: m_scene(nullptr)
		, m_window(nullptr)
	{

	}

	void Framework::Initialize()
	{
		InitializeSDL();
		InitializeEvents();

		// ���ҽ� �ε�

		Resource::instance().LoadAssets();
	}

	void Framework::Run()
	{
		// �޽��� ����
		SDL_Event event;
		while (1)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					Release();

				auto result = m_events.find(event.type);
				if (result != m_events.end())
					result->second(event);
			}

			if (m_scene)
			{
				m_scene->UpdateFrame();
				m_scene->Render();
			}

			Time::instance().UpdateFrame();
		}
	}

	void Framework::Release()
	{
		if (m_window)
			SDL_DestroyWindow(m_window);

		Renderer::instance().Release();
		SDL_Quit();
		exit(0);
	}

	bool Framework::LoadScene(unique_ptr<Scene> scene)
	{
		if (scene == nullptr)
			return false;

		if (scene == m_scene)
			return false;

		m_scene = move(scene);
		m_scene->Initialize();

		return true;
	}

	void Framework::InitializeSDL()
	{
		// SDL �ʱ�ȭ
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			cout << "SDL Initialization Fail: " << SDL_GetError() << endl;
			SDL_Quit();
		}

		// ������ â ����
		m_window = SDL_CreateWindow("SDL2 Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1280, 720,
			SDL_WINDOW_SHOWN);

		if (!m_window)
		{
			cout << "SDL Initialization Fail: " << SDL_GetError() << endl;
			SDL_Quit();
		}

		if (!Renderer::instance().Create(m_window))
		{
			cout << "Renderer Creation Faild\n";
			Release();
		}
	}

	void Framework::InitializeEvents()
	{
		m_events[SDL_KEYUP] = [](const SDL_Event& evt) { Key::instance().OnKeyUp(evt.key.keysym.sym); };
		m_events[SDL_KEYDOWN] = [](const SDL_Event& evt) { Key::instance().OnKeyDown(evt.key.keysym.sym); };
		m_events[SDL_MOUSEMOTION] = [](const SDL_Event& evt) { Key::instance().OnMouseMotion(evt.motion); };
		m_events[SDL_MOUSEBUTTONDOWN] = [](const SDL_Event& evt) { Key::instance().OnMouseButton(evt.button); };
		m_events[SDL_MOUSEWHEEL] = [](const SDL_Event& evt) { Key::instance().OnMouseWheel(evt.wheel); };
	}
}
