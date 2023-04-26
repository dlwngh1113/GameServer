#pragma once

class Scene;

class Framework
{
private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{ nullptr };

    Scene* m_scene;

    void Render();
    void Update();
public:
    Framework();
    virtual ~Framework();

    void Run();
};