#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Player.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	if (m_player)
		delete m_player;

	for (auto& obj : m_objects)
		delete obj;
	m_objects.clear();
}

void Scene::Run()
{

}
