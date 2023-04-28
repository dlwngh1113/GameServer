#include "pch.h"
#include "Framework.h"
#include "Scene.h"
#include "Singleton.h"
#include "Renderer.h"
#include "InGameScene.h"

Framework::Framework()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_INIT failed " << SDL_GetError() << std::endl;
        exit(0);
    }

    if (SDL_CreateWindowAndRenderer(640, 480, 0, &m_window, &Singleton<Renderer>::GetInstance()->GetRenderer()) < 0)
    {
        std::cout << "SDL_CreateWindowAndRenderer Error: " << SDL_GetError() << std::endl;
        exit(0);
    }

    SDL_SetWindowTitle(m_window, "SMO");

    m_renderer = Singleton<Renderer>::GetInstance()->GetRenderer();
    m_scene = new InGameScene;
}

Framework::~Framework()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    delete m_scene;
}

void Framework::Render()
{
    SDL_RenderClear(m_renderer);
    m_scene->Render(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Framework::Update()
{
    m_scene->Update();
}

void Framework::Run()
{
    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            
            default:
                break;
            }
        }
        m_scene->Update();

        Render();
    }
}