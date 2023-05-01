#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Update() = 0;
	virtual void OnEvent(SDL_Event& evt) = 0;
};