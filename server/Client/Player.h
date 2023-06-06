#pragma once
#include "MovableObject.h"

class Player : public MovableObject
{
private:
	SDL_Texture* m_texture{ nullptr };

public:
	Player();
	explicit Player(int nX, int nY, int nWidth, int nHeight);
	virtual ~Player();

	virtual void Update(float flElapsedTime) override;
	virtual void Render(SDL_Renderer* renderer) override;

	virtual void Move(int nDx, int nDy) override;
};
