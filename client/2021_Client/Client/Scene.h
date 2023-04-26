#pragma once

class Object;
class Player;

class Scene
{
protected:
	Player* m_player{ nullptr };
	std::vector<Object*> m_objects;

public:
	Scene();
	virtual ~Scene();

	void Run();
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Update() = 0;
};