#include "pch.h"
#include "Framework.h"
#include "Scene.h"
#include "PacketSender.h"
#include "NetworkManager.h"

Framework Framework::s_instance;

Framework::Framework()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_INIT failed " << SDL_GetError() << std::endl;
        exit(0);
    }

    if (SDL_CreateWindowAndRenderer(640, 480, 0, &m_window, &m_renderer) < 0)
    {
        std::cout << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError() << std::endl;
        exit(0);
    }

    SDL_SetWindowTitle(m_window, "SMO");

    m_scene = make_unique<Scene>();
}

void Framework::Initialize()
{
    if (!NetworkManager::GetInstance().Initialize())
        Release();
}

Framework::~Framework()
{
    Release();
}

void Framework::Release()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Framework::ChangeScene(Scene* scene)
{
    if (scene == nullptr)
        return;
    
    if (m_scene.get() == scene)
        return;

    m_scene.reset(scene);
}

void Framework::ShowError(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", message, m_window);
}

void Framework::Render()
{
    SDL_RenderClear(m_renderer);
    m_scene->Render(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Framework::Update()
{
    NetworkManager::GetInstance().Service();
    m_scene->Update();
}

void Framework::Run()
{
    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
            m_scene->OnEvent(event);

        Update();

        Render();
    }
}