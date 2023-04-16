#pragma once

class Scene;

class Framework
{
private:
    SDL_Window* m_window{nullptr};

    Scene* scene;
public:
    Framework();
    virtual ~Framework();

    void Run();    
};