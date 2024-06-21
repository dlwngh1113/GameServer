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
        , m_worldCamera(nullptr)
        , m_windowSize()
    {
    }

    void Scene::Initialize(const SDL_Point& windowSize)
    {
        m_windowSize = windowSize;

        m_window = (Window*)UIManager::instance().GetUI(UIType::Window);
        
        m_label = m_window->CreateChild<Label>();
        m_label->SetParentPosition(0, 0);
        m_label->SetSize(200, 20);

        m_worldCamera = std::make_unique<Camera>();
    }

    void Scene::Render()
    {
        SDL_Renderer* pRenderer = Renderer::instance().renderer();

        SDL_RenderClear(pRenderer);

        for (const auto& object : m_objects)
            object->Render(pRenderer, m_worldCamera->pos());

        m_window->Render(pRenderer);

        SDL_RenderPresent(pRenderer);
    }

    void Scene::UpdateFrame()
    {
        for (auto& object : m_objects)
            object->UpdateFrame();

        m_window->UpdateFrame();
        m_worldCamera->UpdateFrame();
    }

    void Scene::SetPlayer(std::unique_ptr<Player> player)
    {
        m_player = player.get();

        m_worldCamera->SetTarget(m_player);
        m_worldCamera->SetOffset(m_windowSize.x / 2, m_windowSize.y / 2);

        AddObject(std::move(player));
    }

    void Scene::AddObject(std::unique_ptr<Object> object)
    {
        m_objects.emplace_back(std::move(object));
    }

    void Scene::OnWindowSizeChanged(int width, int height)
    {
        m_windowSize.x = width;
        m_windowSize.y = height;

        m_worldCamera->SetOffset(m_windowSize.x, m_windowSize.y);
    }

    //
    // Static member functions
    //

    Scene* Scene::currentScene()
    {
        return Framework::instance().scene(); 
    }
}
