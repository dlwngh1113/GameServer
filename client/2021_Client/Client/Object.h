#pragma once

class Object
{
protected:
	SDL_Rect m_position{ NULL };
	SDL_Rect m_resourcePosition{ NULL };

public:
	Object();
	explicit Object(int nX, int nY, int nWidth, int nHeight);
	virtual ~Object();

	virtual void Update(float flElapsedTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
};