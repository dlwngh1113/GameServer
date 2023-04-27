#pragma once
#include "Scene.h"

class InGameScene : public Scene
{
private:
	Player* m_player{ nullptr };
	std::vector<Object*> m_objects;

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update() override;
};

