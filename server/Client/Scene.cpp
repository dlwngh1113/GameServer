#include "pch.h"
#include "Scene.h"
#include "Renderer.h"
#include "Label.h"
#include "Window.h"
#include "Framework.h"
#include "UIManager.h"

namespace ClientFramework
{
    Scene::Scene()
        : m_player(nullptr)
        , m_window(nullptr)
        , m_label(nullptr)
    {
    }

    void Scene::Initialize()
    {
        m_window = (Window*)UIManager::instance().GetUI(UIType::Window);
        m_label = m_window->CreateChild<Label>();
        m_label->SetParentPosition(0, 0);
        m_label->SetSize(200, 20);
        m_player = std::make_unique<Player>();
    }

    void Scene::Render()
    {
        SDL_Renderer* pRenderer = Renderer::instance().renderer();

        SDL_RenderClear(pRenderer);

        for (const auto& object : m_objects)
            object->Render(pRenderer);

        if (m_player)
            m_player->Render(pRenderer);

        if (m_window)
            m_window->Render(pRenderer);

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
