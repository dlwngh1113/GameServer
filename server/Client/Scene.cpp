#include "pch.h"
#include "Scene.h"
#include "Renderer.h"
#include "Window.h"
#include "Framework.h"

namespace ClientFramework
{
    Scene::Scene()
        : m_player(nullptr)
        , m_window(nullptr)
    {
    }

    void Scene::Initialize()
    {
        m_window = std::make_unique<Window>();
    }

    void Scene::Render()
    {
        SDL_Renderer* pRenderer = Renderer::instance().renderer();

        SDL_RenderClear(pRenderer);

        for (const auto& object : m_objects)
            object->Render();

        if (m_player)
            m_player->Render();

        if (m_window)
            m_window->Render();

        SDL_RenderPresent(pRenderer);
    }

    void Scene::UpdateFrame()
    {
        for (auto& object : m_objects)
            object->UpdateFrame();

        if (m_player)
            m_player->UpdateFrame();

        if (m_window)
            m_window->UpdateFrame();
    }

    void Scene::AddObject(std::unique_ptr<Object> object)
    {
        m_objects.emplace_back(std::move(object));
    }

    void Scene::OnWindowSizeChanged(int width, int height)
    {

    }

    //
    // Static member functions
    //

    Scene* Scene::currentScene()
    {
        return Framework::instance().scene(); 
    }
}
