#pragma once

class Object;
class MyPlayer;
class OtherPlayer;

class Scene
{
protected:
	MyPlayer* m_myPlayer;
	std::vector<OtherPlayer*> m_otherPlayers;

public:
	Scene();
	virtual ~Scene();

	virtual void Render(SDL_Renderer* renderer);
	virtual void Update();
	virtual void OnEvent(SDL_Event& evt);
};