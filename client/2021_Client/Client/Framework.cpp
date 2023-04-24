#include "pch.h"
#include "Framework.h"

Framework::Framework()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_INIT failed " << SDL_GetError() << std::endl;
        exit(0);
    }

    m_window = SDL_CreateWindow("Test Client", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 720, 0);

    if (!m_window)
    {
        std::cout << "SDL_CREATE_WINDOW failed " << SDL_GetError() << std::endl;
        exit(0);
    }
}

Framework::~Framework()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    delete scene;
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
    }
    return;
}