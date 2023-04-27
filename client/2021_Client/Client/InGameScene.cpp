#include "pch.h"
#include "InGameScene.h"
#include "Player.h"

InGameScene::InGameScene() : Scene()
{
	m_player = new Player(0, 0, 64, 64);
}

InGameScene::~InGameScene()
{
	if (m_player)
		delete m_player;

	for (auto& obj : m_objects)
		delete obj;
	m_objects.clear();
}

void InGameScene::Render(SDL_Renderer* renderer)
{
	m_player->Render(renderer);
}

void InGameScene::Update()
{
}
