#pragma once

class Object;
class Player;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Run() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Update() = 0;
};