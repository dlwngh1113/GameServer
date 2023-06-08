#pragma once

class Object;
class MyPlayer;
class OtherPlayer;

class Scene
{
protected:
	MyPlayer* m_myPlayer{ nullptr };
	std::vector<OtherPlayer*> m_otherPlayers;

public:
	Scene();
	virtual ~Scene();

	virtual void Render(SDL_Renderer* renderer);
	virtual void Update();
	virtual void OnEvent(SDL_Event& evt);

public:
	void SetPlayer(MyPlayer* player) { m_myPlayer = player; }
	const MyPlayer* GetPlayer() const { return m_myPlayer; }

	void AddOtherPlayer(OtherPlayer* otherPlayer);
	OtherPlayer* GetOtherPlayer(int nId);
	void RemoveOtherPlayer(OtherPlayer* otherPlayer);
};