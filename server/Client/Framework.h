#pragma once

class Scene;

class Framework
{
private:
    static Framework s_instance;

    SDL_Window* m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr };

    unique_ptr<Scene> m_scene{ nullptr };

    void Render();
    void Update();

private:
    Framework();

public:
    virtual ~Framework();

    void Initialize();
    void Run();
    void Release();
    void ChangeScene(Scene* scene);

    void ShowError(const char* message);

public:
    Scene* GetScene() { return m_scene.get(); }

    static Framework& GetInstance() { return s_instance; }
};