#pragma once

class CScene;

class CFramework
{
private:
    SDL_Window* m_window{nullptr};

    CScene* scene;
public:
    CFramework();
    virtual ~CFramework();

    void Run();    
};