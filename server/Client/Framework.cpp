#include "pch.h"
#include "Framework.h"
#include "Renderer.h"
#include "Key.h"
#include "Time.h"
#include "Resource.h"
#include "NetworkManager.h"
#include "UIManager.h"

namespace ClientFramework
{
	Framework::Framework()
		: m_scene(nullptr)
		, m_window(nullptr)
		, m_windowSize{ 1280, 720 }
	{

	}

	void Framework::Initialize()
	{
		InitializeSDL();
		InitializeEvents();

		// 리소스 로드
		Resource::instance().LoadAssets();

		// UIManager
		UIManager::instance().Initialize();

		// 네트워크 연결
		if (!NetworkManager::instance().Initialize())
			Release();

		// 로그인 패킷 전송
		std::shared_ptr<Common::LoginCommandBody> body = std::make_shared<Common::LoginCommandBody>();
		body->userId = "dlwngh";
		body->password = "ljh1348";
		NetworkManager::instance().SendPacket(body);

		// Scene 추가
		m_scene = std::make_unique<Scene>();
		m_scene->Initialize(m_windowSize);
	}

	void Framework::Run()
	{
		// 메시지 루프
		SDL_Event event;
		SDL_Point windowSize;

		while (1)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					exit(0);

				auto result = m_events.find(event.type);
				if (result != m_events.end())
					result->second(event);
			}

			if (m_scene)
			{
				m_scene->UpdateFrame();
				m_scene->Render();

				SDL_GetWindowSize(m_window, &windowSize.x, &windowSize.y);

				if (windowSize.x != m_windowSize.x || windowSize.y != m_windowSize.y)
					m_scene->OnWindowSizeChanged(windowSize.x, windowSize.y);
			}

			NetworkManager::instance().Service();
			Time::instance().UpdateFrame();
		}
	}

	void Framework::Release()
	{
		if (m_window)
			SDL_DestroyWindow(m_window);

		Renderer::instance().Release();
		IMG_Quit();
		SDL_Quit();
		exit(0);
	}

	bool Framework::LoadScene(std::unique_ptr<Scene> scene)
	{
		if (scene == nullptr)
			return false;

		if (scene == m_scene)
			return false;

		m_scene = std::move(scene);
		m_scene->Initialize(m_windowSize);

		return true;
	}

	void Framework::InitializeSDL()
	{
		// SDL 초기화
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL Initialization Fail: " << SDL_GetError() << std::endl;
			exit(0);
		}

		if (TTF_Init() < 0)
		{
			std::cout << "SDL Font Initialization Fail: " << SDL_GetError() << std::endl;
			exit(0);
		}

		int imageFlag = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlag) & imageFlag))
		{
			std::cout << "SDL Image Initialization Fail: " << IMG_GetError() << std::endl;
			exit(0);
		}

		atexit([]() { Framework::instance().Release(); });

		// 윈도우 창 생성
		m_window = SDL_CreateWindow("SDL2 Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			m_windowSize.x, m_windowSize.y,
			SDL_WINDOW_SHOWN);

		if (!m_window)
		{
			std::cout << "SDL Initialization Fail: " << SDL_GetError() << std::endl;
			exit(0);
		}

		if (!Renderer::instance().Create(m_window))
		{
			std::cout << "Renderer Creation Faild\n";
			exit(0);
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
