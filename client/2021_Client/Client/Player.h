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

	virtual void Update(float flElapsedTime);
	virtual void Render(SDL_Renderer* renderer);

	virtual void Move(int nDx, int nDy);
};
