#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Player.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Render(SDL_Renderer* renderer)
{

}

void Scene::Update()
{
}

void Scene::OnEvent(SDL_Event& evt)
{
}

void Scene::AddOtherPlayer(OtherPlayer* otherPlayer)
{
	m_otherPlayers.push_back(otherPlayer);
}

OtherPlayer* Scene::GetOtherPlayer(int nId)
{
	OtherPlayer* value{ nullptr };

	for (const auto& player : m_otherPlayers)
		;

	return value;
}

void Scene::RemoveOtherPlayer(OtherPlayer* otherPlayer)
{
	for (auto i = m_otherPlayers.begin(); i != m_otherPlayers.end(); ++i)
		if (*i == otherPlayer)
			m_otherPlayers.erase(i);
}
