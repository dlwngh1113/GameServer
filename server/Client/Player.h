#pragma once
#include "MovableObject.h"

class Player : public MovableObject
{
private:
	SDL_Texture* m_texture{ nullptr };

protected:
	int m_nId{ 0 };

public:
	Player();
	virtual ~Player();

	int id() const { return m_nId; }

	virtual void Update(float flElapsedTime) override;
	virtual void Render(SDL_Renderer* renderer) override;

	virtual void Move(int nX, int nY) override;
};
