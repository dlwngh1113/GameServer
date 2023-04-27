#pragma once
#include "Scene.h"

class InGameScene : public Scene
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update() override;
};

