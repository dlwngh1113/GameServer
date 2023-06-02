#pragma once

class Scene;

class Framework
{
private:
    static Framework s_instance;

    SDL_Window* m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr };

    Scene* m_scene{ nullptr };

    void Release();

    void Render();
    void Update();

private:
    Framework();

public:
    virtual ~Framework();

    static Framework& GetInstance() { return s_instance; }

    void Run();
};