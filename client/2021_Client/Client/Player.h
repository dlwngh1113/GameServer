#pragma once
#include "MovableObject.h"

class Player : public MovableObject
{
private:
	SDL_Surface* m_surface{ nullptr };

public:
	Player();
	Player(int nX, int nY, int nWidth, int nHeight);
	virtual ~Player();

	virtual void Update(float flElapsedTime);
	virtual void Render();

	virtual void Move(int nDx, int nDy);
};
