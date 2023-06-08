#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Player.h"
#include "MyPlayer.h"
#include "OtherPlayer.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	if (m_myPlayer)
		delete m_myPlayer;
	for (auto& otherPlayer : m_otherPlayers)
		delete otherPlayer;
}

void Scene::Render(SDL_Renderer* renderer)
{
	if (m_myPlayer)
		m_myPlayer->Render(renderer);
	for (const auto& otherPlayer : m_otherPlayers)
		otherPlayer->Render(renderer);
}

void Scene::Update()
{
	if (m_myPlayer)
		m_myPlayer->Update(0);
	for (const auto& otherPlayer : m_otherPlayers)
		otherPlayer->Update(0.0f);
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
